#!/usr/bin/env python3
"""Bucket near-miss functions by the kind of instruction diff they show.

Runs objdiff-cli over every unit that has both a target and a built object,
looks at each function with 0 < match% < 100, and assigns it one primary
bucket from the instruction-level diff. Functions that share a bucket and
subtype usually share a cause (flag, compiler version, header, pragma), so a
cluster is worth investigating once instead of per function.

  python3 tools/near_miss.py                     # summary of all near misses
  python3 tools/near_miss.py --list SCHEDULE     # functions in a bucket
  python3 tools/near_miss.py --list REGALLOC:rename --limit 20
  python3 tools/near_miss.py --unit nw4r/ef      # restrict to units by substring
  python3 tools/near_miss.py --min-pct 90        # only the closest misses
  python3 tools/near_miss.py --renames           # symbols.txt rename candidates
  python3 tools/near_miss.py --shape --skip-tried --min-pct 80   # hand-fixable control-flow shape
  python3 tools/near_miss.py --shape --hint double-cond          # one pattern across the project

Buckets (first rule that applies wins):
  NV-REGS        callee-saved register count differs (register pressure,
                 temp lifetimes, inlining); subtype is ours-minus-target
  CALLS          `bl` count differs (inlining / extra or missing calls)
  BRANCH-SHAPE   same calls, different branch opcodes (condition polarity,
                 loop form, switch lowering, block layout)
  CMP-SIGN       only compare opcodes differ (signed vs unsigned)
  EXT-CAST       only extend/mask opcodes differ (casts, bitfield access)
  FLOAT          only float opcodes differ (conversions, fused ops)
  OPS-OTHER      other instruction-selection differences
  SCHEDULE       same instruction multiset, different order
  STACK-LAYOUT   same code, different r1-relative offsets (locals/temps order)
  RELOC          same code, but a call goes to a different function
  DATA-REF       same code, only data references differ: subtype pool (both
                 unnamed: lbl_XXXX vs @NNNN), sym (different named symbol) or
                 hidden (same printed text, different relocation target).
                 Usually unmatched data layout/naming, not a codegen problem.
                 Other buckets carry a "+D" mark when they also have these.
  IMM            same code, different immediate (constants, struct offsets)
  REGALLOC       same code, register operands only; subtype `rename` when one
                 consistent register mapping explains every diff, else `mixed`
  BRANCH-DEST    only branch destinations differ

Shape hints (independent of the bucket; `--shape` lists them, JSON key
"hints"). Each is a pattern that was fixed by a source change at least once
(docs/lessons/2026-10-16-label-only-diffs-*, -branch-shape-*, -double-beq-*):
  join-moved     branch-target labels sit at different rows: the target's
                 join point differs, e.g. code that runs on every path was put
                 inside the last switch case / an if (move it after it)
  one-case-switch  target `beq X; b END; X:` = switch (v) { case K: } written
                 as if (v == K) in ours
  double-cond    target repeats a conditional branch on the same compare
                 (beq; beq): nested redundant null check, e.g. an inlined
                 intermediate-base dtor (lesson double-beq-in-dtor)
  extra-cmp      target has more compares: the original wrote a redundant
                 condition literally ((a>=K && d>=K) || (a<K && d>=K))
  fewer-cmp      ours has more compares: a condition was over-expanded
  ret-mask       a clrlwi/extsb follows a call on one side only: callee
                 declared u8/bool vs s32/int (fix the prototype, not a cast)
  early-return   conditional return (beqlr/bnelr) on one side only
  loop-ctr       mtctr/bdnz on one side only: loop form (for vs do-while)
  returns-self   target ends with mr r3,<saved reg>: ctor-like fn returns self
Functions with no hint and bucket REGALLOC/SCHEDULE rarely close by hand;
`--shape` sorts hinted ones first and `--skip-tried` drops functions whose
routing log (build/evidence/routing-log.jsonl) already records a nogain.

Only code is scored per function. Non-code sections are reported at unit level
(units whose code is exact but whose data is not). Output is advisory: the
buckets are heuristics over objdiff's aligned diff, not proof of cause.
Run from the repo root, or pass --root to point at a built checkout (the
tool only reads; it never builds).
"""
import argparse
import json
import os
import re
import subprocess
import sys
import tempfile
from collections import Counter, defaultdict
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

REG = re.compile(r"^(r|f)\d+$|^cr\d$|^(lr|ctr|xer)$")
NV_GPR = re.compile(r"^r(1[4-9]|2\d|3[01])$")
NV_FPR = re.compile(r"^f(1[4-9]|2\d|3[01])$")
CMP = {"cmpw", "cmplw", "cmpwi", "cmplwi"}
EXT = {"extsb", "extsh", "clrlwi", "clrlwi.", "rlwinm", "rlwinm.", "rlwimi", "rlwnm", "extsb.", "extsh."}
FLT_PREFIX = ("lf", "stf", "fm", "fa", "fs", "fn", "fr", "fc", "psq", "ps_")


def parse_args(insn: dict):
    """Return [(kind, value)] for the instruction's operands."""
    out = []
    for p in insn.get("parts", []):
        a = p.get("arg")
        if a is None:
            continue
        if "opaque" in a:
            v = a["opaque"]
            out.append(("reg" if REG.match(v) else "opaque", v))
        elif "signed" in a or "unsigned" in a:
            out.append(("imm", a.get("signed", a.get("unsigned"))))
        elif "branch_dest" in a:
            out.append(("br", str(a["branch_dest"])))
        elif "reloc" in a:
            out.append(("reloc", ""))
        else:
            out.append(("opaque", json.dumps(a, sort_keys=True)))
    return out


def mnemonic(insn: dict) -> str:
    for p in insn.get("parts", []):
        if "opcode" in p:
            return p["opcode"]["mnemonic"]
    return "?"


UNNAMED = re.compile(r"^(@.*|lbl_[0-9A-Fa-f]+|\$\d+)$")  # compiler-made (@123, @STRING@..) or auto-named
DATA_RELOC = re.compile(r"([^\s,()]+?)@(?:sda21|sda2|ha|l|h|sdarel)\b")


def reloc_name(row: dict, syms: list | None = None) -> str | None:
    """Symbol the instruction relocates against (symbol table first, printed text as fallback)."""
    ins = row.get("instruction")
    if not ins or not ins.get("relocation"):
        return None
    idx = ins["relocation"].get("target_symbol")
    if syms is not None and isinstance(idx, int) and 0 <= idx < len(syms) and syms[idx].get("name"):
        return syms[idx]["name"]
    text = ins.get("formatted", "")
    m = DATA_RELOC.search(text)
    if m:
        return m.group(1)
    return text.split()[-1] if text.split() else None


def reloc_diff(lr: dict, rr: dict, ls=None, rs=None):
    """None if the relocation targets agree, else (kind, target_name, our_name); kind is pool, call or sym."""
    ln, rn = reloc_name(lr, ls), reloc_name(rr, rs)
    if ln == rn:
        return None
    if ln and rn and UNNAMED.match(ln) and UNNAMED.match(rn):
        return "pool", ln, rn
    if lr["instruction"].get("formatted", "").startswith(("bl ", "b ")):
        return "call", ln, rn
    return "sym", ln, rn


def nv_regs(rows):
    g, f = set(), set()
    for row in rows:
        for kind, v in parse_args(row.get("instruction", {})):
            if kind == "reg":
                if NV_GPR.match(v):
                    g.add(v)
                elif NV_FPR.match(v):
                    f.add(v)
    return len(g), len(f)


def frame_size(rows):
    for row in rows:
        ins = row.get("instruction")
        if ins and mnemonic(ins) == "stwu":
            a = parse_args(ins)
            if len(a) == 3 and a[0][1] == "r1" and a[2][1] == "r1":
                try:
                    return int(a[1][1])
                except ValueError:
                    return None
    return None


def diff_sig(extra: Counter, missing: Counter, n: int = 3) -> str:
    parts = [f"-{m}" for m, _ in missing.most_common(n)] + [f"+{m}" for m, _ in extra.most_common(n)]
    return " ".join(parts[:n * 2]) or "none"


def classify(lrows, rrows, lsyms=None, rsyms=None):
    """lrows = target side, rrows = our side, aligned (gaps carry no instruction)."""
    lins = [r["instruction"] for r in lrows if "instruction" in r]
    rins = [r["instruction"] for r in rrows if "instruction" in r]
    lm = Counter(mnemonic(i) for i in lins)
    rm = Counter(mnemonic(i) for i in rins)
    wrong = sum(1 for r in lrows if r.get("diff_kind") not in (None, "DIFF_NONE"))
    kinds = Counter(r.get("diff_kind") for r in lrows if r.get("diff_kind") not in (None, "DIFF_NONE"))
    idx = [i for i, r in enumerate(lrows) if r.get("diff_kind") not in (None, "DIFF_NONE")]
    span = (idx[0], idx[-1], len(lrows)) if idx else (0, 0, len(lrows))
    info = {"wrong": wrong, "insns": len(lins), "delta_insns": len(rins) - len(lins),
            "span": span, "kinds": dict(kinds)}

    lg, lf = nv_regs(lrows)
    rg, rf = nv_regs(rrows)
    if (lg, lf) != (rg, rf):
        sub = []
        if rg != lg:
            sub.append(f"{rg - lg:+d}gpr")
        if rf != lf:
            sub.append(f"{rf - lf:+d}fpr")
        return "NV-REGS", " ".join(sub), info

    extra, missing = rm - lm, lm - rm
    if extra or missing:
        if lm.get("bl", 0) != rm.get("bl", 0):
            return "CALLS", f"{rm.get('bl', 0) - lm.get('bl', 0):+d}bl", info
        br = lambda c: Counter({m: n for m, n in c.items() if m[0] == "b"})
        if br(lm) != br(rm):
            return "BRANCH-SHAPE", diff_sig(br(extra), br(missing)), info
        dm = set(extra) | set(missing)
        sig = diff_sig(extra, missing)
        if dm <= CMP:
            return "CMP-SIGN", sig, info
        if dm <= EXT:
            return "EXT-CAST", sig, info
        if all(m.startswith(FLT_PREFIX) for m in dm):
            return "FLOAT", sig, info
        return "OPS-OTHER", sig, info

    if any(k in kinds for k in ("DIFF_INSERT", "DIFF_DELETE", "DIFF_REPLACE", "DIFF_OP_MISMATCH")):
        return "SCHEDULE", ("+args" if "DIFF_ARG_MISMATCH" in kinds else "pure"), info

    # Same instruction multiset, only operand mismatches remain.
    pairs, has_stack, has_imm, has_reloc, has_br, has_reg = {}, False, False, False, False, False
    consistent, pool, reloc_kinds, renames = True, False, set(), set()
    for lr, rr in zip(lrows, rrows):
        if lr.get("diff_kind") != "DIFF_ARG_MISMATCH" or "instruction" not in lr or "instruction" not in rr:
            continue
        la, ra = parse_args(lr["instruction"]), parse_args(rr["instruction"])
        mism = {d_i for d_i, d in enumerate(lr.get("arg_diff", [])) if d}
        uses_r1 = any(v == "r1" for _, v in la)
        for i in mism:
            if i >= len(la) or i >= len(ra):
                # objdiff lists the relocation as an extra slot that the printed text omits
                has_reloc = True
                reloc_kinds.add("hidden")
                continue
            (lk, lv), (rk, rv) = la[i], ra[i]
            if lk == "reg" and rk == "reg":
                has_reg = True
                if pairs.setdefault(lv, rv) != rv:
                    consistent = False
            elif lk == "imm":
                if uses_r1:
                    has_stack = True
                else:
                    has_imm = True
            elif lk == "br":
                has_br = True
            elif lk == "reloc":
                pass  # judged below by symbol name, not by objdiff's per-side symbol index
            else:
                has_imm = True
        rd = reloc_diff(lr, rr, lsyms, rsyms)
        if rd is None:
            pass
        elif rd[0] == "pool":
            pool = True
        else:
            has_reloc = True
            reloc_kinds.add(rd[0])
            if rd[0] == "sym" and rd[1] and rd[2] and UNNAMED.match(rd[1]) and not UNNAMED.match(rd[2]):
                renames.add((rd[1], rd[2]))
    if len(set(pairs.values())) != len(pairs):
        consistent = False
    dataref = pool or bool(reloc_kinds - {"call"})
    info["dataref"] = dataref
    info["renames"] = sorted(renames)
    if has_stack:
        lf_, rf_ = frame_size(lrows), frame_size(rrows)
        sub = f"frame{rf_ - lf_:+d}" if lf_ is not None and rf_ is not None and lf_ != rf_ else "same-frame"
        return "STACK-LAYOUT", sub, info
    if has_imm:
        return "IMM", "", info
    if has_reg:
        return "REGALLOC", ("rename" if consistent else "mixed"), info
    if "call" in reloc_kinds:
        return "RELOC", "call", info
    if dataref:
        kinds_ = sorted(reloc_kinds - {"call"} | ({"pool"} if pool else set()))
        return "DATA-REF", "+".join(kinds_), info
    if has_br:
        return "BRANCH-DEST", "", info
    return "OPS-OTHER", "unknown", info


COND_BR = re.compile(r"^b(eq|ne|lt|le|gt|ge|so|ns|dnz|dz)[+-]?$")
COND_RET = re.compile(r"^b(eq|ne|lt|le|gt|ge|so|ns)lr[+-]?$")
MASK = {"clrlwi", "clrlwi.", "extsb", "extsb.", "extsh", "extsh.", "rlwinm."}


def _seq(rows):
    """(mnemonic, args, address, branch_dest) per real instruction."""
    out = []
    for r in rows:
        ins = r.get("instruction")
        if not ins:
            continue
        out.append((mnemonic(ins), parse_args(ins), ins.get("address"), ins.get("branch_dest")))
    return out


def label_rows(rows):
    """Aligned-row flags: True where the row's instruction is a branch target."""
    dests = {r["instruction"].get("branch_dest") for r in rows if "instruction" in r}
    dests.discard(None)
    return [("instruction" in r and r["instruction"].get("address") in dests) for r in rows]


def _count(seq, pred):
    return sum(1 for i in range(len(seq)) if pred(seq, i))


def _one_case(seq, i):
    if i + 2 >= len(seq) or not COND_BR.match(seq[i][0]) or seq[i + 1][0] != "b":
        return False
    return seq[i][3] is not None and seq[i][3] == seq[i + 2][2]


def _double_cond(seq, i):
    return i + 1 < len(seq) and COND_BR.match(seq[i][0]) and seq[i][0] == seq[i + 1][0] \
        and not seq[i][0].startswith("bd")


def _mask_after_call(seq, i):
    return seq[i][0] == "bl" and any(m in MASK for m, *_ in seq[i + 1:i + 3])


def shape_hints(lrows, rrows):
    """Control-flow / declaration patterns that point at a source-level fix."""
    hints = []
    ll, rl = label_rows(lrows), label_rows(rrows)
    moved = sum(1 for a, b in zip(ll, rl) if a != b)
    if moved:
        hints.append("join-moved")
    ls, rs = _seq(lrows), _seq(rrows)
    if _count(ls, _one_case) > _count(rs, _one_case):
        hints.append("one-case-switch")
    if _count(ls, _double_cond) > _count(rs, _double_cond):
        hints.append("double-cond")
    lc = sum(1 for m, *_ in ls if m in CMP)
    rc = sum(1 for m, *_ in rs if m in CMP)
    if lc > rc:
        hints.append("extra-cmp")
    elif rc > lc:
        hints.append("fewer-cmp")
    if _count(ls, _mask_after_call) != _count(rs, _mask_after_call):
        hints.append("ret-mask")
    if sum(1 for m, *_ in ls if COND_RET.match(m)) != sum(1 for m, *_ in rs if COND_RET.match(m)):
        hints.append("early-return")
    if any(m == "mtctr" for m, *_ in ls) != any(m == "mtctr" for m, *_ in rs) or \
            any(m.startswith("bdnz") for m, *_ in ls) != any(m.startswith("bdnz") for m, *_ in rs):
        hints.append("loop-ctr")
    tail = lambda seq: [(m, a) for m, a, *_ in seq[-8:]]
    self_ret = lambda seq: any(m == "mr" and len(a) == 2 and a[0][1] == "r3" and NV_GPR.match(a[1][1])
                               for m, a in tail(seq))
    if self_ret(ls) and not self_ret(rs):
        hints.append("returns-self")
    return hints, moved


def tried_nogain(path="build/evidence/routing-log.jsonl"):
    """Function names whose routing log records an attempt without a match."""
    out, matched = set(), set()
    p = Path(path)
    if not p.exists():
        return out
    for line in p.read_text().splitlines():
        try:
            d = json.loads(line)
        except ValueError:
            continue
        fn, res = d.get("fn") or d.get("function"), d.get("result")
        if not fn:
            continue
        if res == "match":
            matched.add(fn)
        elif res in ("nogain", "fail"):
            out.add(fn)
    return out - matched


def run_objdiff(objdiff: str, unit: dict) -> dict | None:
    with tempfile.TemporaryDirectory() as tmp:
        out = Path(tmp) / "d.json"
        r = subprocess.run([objdiff, "diff", "-1", unit["target_path"], "-2", unit["base_path"],
                            "-o", str(out), "--format", "json"], capture_output=True, text=True)
        if r.returncode != 0 or not out.exists():
            return None
        return json.loads(out.read_text())


def analyze_unit(args):
    objdiff, unit, lo, hi, depth = args
    name = unit["name"].removeprefix("main/")
    group = "/".join(name.split("/")[:depth])
    data = run_objdiff(objdiff, unit)
    if data is None:
        return name, group, None, [], False, {}
    lsyms, rsyms = data["left"].get("symbols", []), data["right"].get("symbols", [])
    fns, exact, total, scores = [], 0, 0, {}
    for s in lsyms:
        if s.get("kind") != "SYMBOL_FUNCTION":
            continue
        total += 1
        pct = float(s.get("match_percent", 0.0))
        scores[s["name"]] = round(pct, 3)
        if pct == 100.0:
            exact += 1
            continue
        t = s.get("target_symbol")
        if not (lo < pct < hi) or t is None or t >= len(rsyms):
            continue
        r = rsyms[t]
        lrows, rrows = s.get("instructions", []), r.get("instructions", [])
        bucket, sub, info = classify(lrows, rrows, lsyms, rsyms)
        info["hints"], info["labels_moved"] = shape_hints(lrows, rrows)
        fns.append({"unit": name, "group": group, "fn": s.get("demangled_name") or s["name"],
                    "sym": s["name"], "pct": round(pct, 2), "size": int(s.get("size", 0)),
                    "bucket": bucket, "sub": sub, **info})
    data_bad = [x["name"] for x in data["left"].get("sections", [])
                if x.get("kind") == "SECTION_DATA" and float(x.get("match_percent", 100.0)) < 100.0]
    return name, group, (exact, total), fns, bool(data_bad), scores


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--root", default=".", help="built checkout to read (default: cwd)")
    ap.add_argument("--unit", action="append", default=[], help="only units whose name contains this (repeatable)")
    ap.add_argument("--min-pct", type=float, default=0.0, help="exclude functions at or below this match%%")
    ap.add_argument("--max-pct", type=float, default=100.0, help="exclude functions at or above this match%%")
    ap.add_argument("--list", metavar="BUCKET[:SUB]", help="list functions in a bucket, easiest (fewest wrong insns) first")
    ap.add_argument("--limit", type=int, default=25, help="rows for --list and tables (default 25)")
    ap.add_argument("--group-depth", type=int, default=2, help="path components that form a library group (default 2)")
    ap.add_argument("--shape", action="store_true",
                    help="list functions with control-flow shape hints (see docstring), most tractable first")
    ap.add_argument("--hint", metavar="NAME", help="with --shape/--list: only functions carrying this hint")
    ap.add_argument("--skip-tried", action="store_true",
                    help="drop functions whose routing log records a nogain/fail attempt without a later match")
    ap.add_argument("--exclude", action="append", default=[],
                    help="drop units whose name contains this (repeatable; e.g. owned/claimed objects)")
    ap.add_argument("--renames", action="store_true",
                    help="suggest symbols.txt renames: target-side lbl_XXXX that our build names (code already matches)")
    ap.add_argument("--save-scores", metavar="PATH", help="write every function's match%% (all units) as JSON")
    ap.add_argument("--vs-scores", metavar="PATH", help="compare against a --save-scores file; print regressions/improvements")
    ap.add_argument("--json", metavar="PATH", help="write the full per-function report as JSON")
    ap.add_argument("-j", "--jobs", type=int, default=os.cpu_count() or 4)
    a = ap.parse_args()

    os.chdir(a.root)
    objdiff = "build/tools/objdiff-cli"
    if not Path(objdiff).exists():
        sys.exit(f"near_miss: {objdiff} not found under {Path.cwd()}")
    units = json.loads(Path("objdiff.json").read_text())["units"]
    todo = [u for u in units
            if u.get("base_path") and Path(u["base_path"]).exists() and Path(u["target_path"]).exists()
            and (not a.unit or any(q in u["name"] for q in a.unit))]
    with ThreadPoolExecutor(a.jobs) as ex:
        results = list(ex.map(analyze_unit, [(objdiff, u, a.min_pct, a.max_pct, a.group_depth) for u in todo]))

    fns = [f for _, _, _, fl, _, _ in results for f in fl]
    if a.exclude:
        fns = [f for f in fns if not any(q in f["unit"] for q in a.exclude)]
    if a.skip_tried:
        tried = tried_nogain()
        fns = [f for f in fns if f["sym"] not in tried]
    if a.hint:
        fns = [f for f in fns if a.hint in f.get("hints", [])]
    failed = [n for n, _, st, _, _, _ in results if st is None]
    exact = sum(st[0] for _, _, st, _, _, _ in results if st)
    total = sum(st[1] for _, _, st, _, _, _ in results if st)
    data_only = [n for n, _, st, fl, bad, _ in results if st and st[0] == st[1] and bad]

    if a.json:
        Path(a.json).parent.mkdir(parents=True, exist_ok=True)
        Path(a.json).write_text(json.dumps(fns, indent=1))

    if a.save_scores or a.vs_scores:
        cur = {n: sc for n, _, st, _, _, sc in results if st}
        if a.save_scores:
            Path(a.save_scores).parent.mkdir(parents=True, exist_ok=True)
            Path(a.save_scores).write_text(json.dumps(cur))
            print(f"saved scores for {len(cur)} units ({sum(len(v) for v in cur.values())} fns) -> {a.save_scores}")
        if a.vs_scores:
            old = json.loads(Path(a.vs_scores).read_text())
            reg, imp, gone = [], [], 0
            for n, fs in cur.items():
                for fn, pct in fs.items():
                    was = old.get(n, {}).get(fn)
                    if was is None:
                        continue
                    if pct < was - 1e-3:
                        reg.append((n, fn, was, pct))
                    elif pct > was + 1e-3:
                        imp.append((n, fn, was, pct))
                gone += sum(1 for fn in old.get(n, {}) if fn not in fs)
            print(f"vs {a.vs_scores}: {len(imp)} improved, {len(reg)} regressed, {gone} functions no longer present")
            for tag, rows in (("REGRESSED", reg), ("improved", imp)):
                for n, fn, was, pct in sorted(rows, key=lambda r: r[3] - r[2])[:a.limit]:
                    print(f"  {tag:9} {was:6.2f} -> {pct:6.2f}  {n} :: {fn[:60]}")
        return

    if a.renames:
        cand = defaultdict(lambda: defaultdict(set))
        for f in fns:
            for old, new in f.get("renames", []):
                cand[(f["unit"], old)][new].add(f["fn"])
        clean = {k: v for k, v in cand.items() if len(v) == 1}
        print(f"{len(cand)} unnamed target symbols that our build names; {len(clean)} map to a single name, "
              f"{len(cand) - len(clean)} conflict (one lbl_ -> several names: likely a wrong split or merged symbol)")
        for (unit, old), v in sorted(clean.items())[:a.limit]:
            (new, users), = v.items()
            print(f"  {unit}: {old} -> {new}  ({len(users)} fn)")
        for (unit, old), v in sorted(cand.items()):
            if len(v) > 1:
                print(f"  CONFLICT {unit}: {old} -> {', '.join(sorted(v))}")
        return

    if a.shape:
        rows = [f for f in fns if f.get("hints")]
        # label moves with few wrong instructions were the cheapest fixes; bucket REGALLOC last
        key = lambda f: (f["bucket"] in ("REGALLOC", "SCHEDULE") and f["hints"] == ["join-moved"],
                         f["wrong"], -f["pct"])
        rows.sort(key=key)
        print(f"shape hints: {len(rows)} of {len(fns)} near misses"
              + "".join(f"; {h} {n}" for h, n in Counter(h for f in rows for h in f["hints"]).most_common()))
        for f in rows[:a.limit]:
            print(f"  {f['pct']:6.2f}% wrong={f['wrong']:<3} lbl={f['labels_moved']:<2} {f['bucket']:<12} "
                  f"{','.join(f['hints']):<28} {f['unit']} :: {f['fn'][:60]}")
        return

    if a.list:
        bk, _, sub = a.list.partition(":")
        rows = sorted((f for f in fns if f["bucket"] == bk.upper() and (not sub or f["sub"] == sub)),
                      key=lambda f: (f["wrong"], -f["pct"]))
        print(f"{bk}{':' + sub if sub else ''}: {len(rows)} fns")
        for f in rows[:a.limit]:
            hs = ",".join(f.get("hints", []))
            print(f"  {f['pct']:6.2f}% wrong={f['wrong']:<3} {f['sub']:<14}{'+D' if f.get('dataref') else '  '} {f['unit']} :: {f['fn'][:70]}"
                  + (f"  [{hs}]" if hs else ""))
        return

    print(f"{len(todo)} units scanned ({len(failed)} diff failures), {exact}/{total} fns exact, "
          f"{len(fns)} near misses ({a.min_pct:g}% < m < {a.max_pct:g}%)")
    by = defaultdict(list)
    for f in fns:
        by[f["bucket"]].append(f)
    print(f"\n{'bucket':<13}{'fns':>5}{'wrong':>7}{'avg%':>7}{'<=4 wrong':>11}  top subtypes")
    for bk, rows in sorted(by.items(), key=lambda kv: -len(kv[1])):
        subs = Counter(f["sub"] or "-" for f in rows).most_common(3)
        print(f"{bk:<13}{len(rows):>5}{sum(f['wrong'] for f in rows):>7}"
              f"{sum(f['pct'] for f in rows) / len(rows):>7.1f}{sum(1 for f in rows if f['wrong'] <= 4):>11}  "
              + ", ".join(f"{s} {n}" for s, n in subs))

    hinted = [f for f in fns if f.get("hints")]
    if hinted:
        print(f"\n{len(hinted)} near misses carry shape hints (source-level control-flow/decl fixes; "
              f"list with --shape): " + ", ".join(f"{h} {n}" for h, n in
                                                   Counter(h for f in hinted for h in f["hints"]).most_common(5)))

    groups = Counter(f["group"] for f in fns)
    print(f"\nbucket mix by group (top {min(a.limit, 12)} groups by near-miss count)")
    for g, n in groups.most_common(min(a.limit, 12)):
        mix = Counter(f["bucket"] for f in fns if f["group"] == g).most_common(4)
        print(f"  {g:<28}{n:>4}  " + ", ".join(f"{b} {c}" for b, c in mix))

    clusters = Counter((f["bucket"], f["sub"]) for f in fns)
    print("\nlargest clusters (bucket:subtype)")
    for (b, s), n in clusters.most_common(10):
        gs = Counter(f["group"] for f in fns if f["bucket"] == b and f["sub"] == s)
        print(f"  {b}:{s or '-':<14}{n:>4} fns in {len(gs)} groups")
    if data_only:
        print(f"\n{len(data_only)} units have exact code but inexact data sections "
              f"(first: {', '.join(data_only[:3])})")
    if failed:
        print(f"diff failed for: {', '.join(failed[:5])}")


if __name__ == "__main__":
    main()
