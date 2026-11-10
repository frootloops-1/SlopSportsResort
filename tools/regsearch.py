#!/usr/bin/env python3
"""Register-order search for one function of one unit.

decomp-permuter needs a C parser and a stand-in object; it fails on C++ and on large float functions.
This tool compiles real source variants with the unit's real ninja compile command and scores them
against the original object with a smoother objective than objdiff percent:

    score = 50*op_wrong + 10*imm_wrong + 4*rank_displacement + 0.25*reg_wrong

  op_wrong    instructions whose mnemonic differs / are missing after aligning the opcode streams
  imm_wrong   same mnemonic, different immediate / symbol / shape
  reg_wrong   register operands that differ in aligned same-shape instructions
  rank        sum over callee-saved roles of |colour rank in original - colour rank in ours| (perm = how many differ)

Variants come from sites: (anchor text, alternatives). Sites are generated from the function body
(declaration hoisting, integer type swaps, adjacent independent statement swaps) and/or read from a
JSON file of hand written sites. See docs/regsearch.md.

    python3 tools/regsearch.py score  <unit> <function> [--src FILE]
    python3 tools/regsearch.py search <unit> <function> [--sites sites.json] [--generic] [-j 4]
                                      [--minutes 10] [--out DIR]
    <unit> e.g. nw4r/ef/ef_animcurve, <function> a substring of the (mangled) symbol name.
"""
from __future__ import annotations

import argparse
import difflib
import os
import hashlib
import json
import math
import random
import re
import shlex
import subprocess
import sys
import threading
import time
from collections import Counter, defaultdict
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
VERSION = "RZTE01_01"
DTK = ROOT / "build" / "tools" / "dtk"


# ---------------------------------------------------------------- compile ---

def unit_source(unit: str) -> Path:
    for ext in (".cpp", ".c"):
        p = ROOT / "src" / f"{unit}{ext}"
        if p.exists():
            return p
    sys.exit(f"no source for {unit}")


def compile_template(unit: str):
    """The unit's real compile command (from ninja) minus -MMD/-c/-o, as a token list."""
    obj = f"build/{VERSION}/src/{unit}.o"
    out = subprocess.run(["ninja", "-t", "commands", obj], cwd=ROOT, capture_output=True, text=True).stdout
    line = [l for l in out.splitlines() if "mwcceppc" in l][-1]
    line = line.split(" && ")[0]
    toks = shlex.split(line)
    clean, skip = [], 0
    for t in toks:
        if skip:
            skip -= 1
            continue
        if t == "-MMD":
            continue
        if t in ("-c", "-o"):
            skip = 1
            continue
        clean.append(t)
    return clean


def compile_variant(tmpl, src: Path, outdir: Path):
    outdir.mkdir(parents=True, exist_ok=True)
    r = subprocess.run(tmpl + ["-c", str(src), "-o", str(outdir)], cwd=ROOT, capture_output=True, text=True)
    obj = outdir / (src.stem + ".o")
    return (obj if obj.exists() and r.returncode == 0 else None), r.stdout + r.stderr


# ----------------------------------------------------------------- disasm ---

def functions(obj: Path, scratch: Path):
    s = scratch / (obj.parent.name + "_" + obj.stem + ".s")
    subprocess.run([str(DTK), "elf", "disasm", str(obj), str(s)], check=True, capture_output=True, cwd=ROOT)
    funcs, cur, labels = {}, None, {}
    for line in s.read_text().splitlines():
        m = re.match(r"\.fn (\S+),", line)
        if m:
            cur = m.group(1)
            funcs[cur] = []
            labels = {}
            continue
        if line.startswith(".endfn"):
            cur = None
            continue
        if cur is None:
            continue
        if not line.startswith("/*"):
            if re.match(r"\.L_[0-9A-Fa-f]+:", line):
                funcs[cur].append("<label>")
            continue
        ins = re.sub(r"^/\*.*?\*/\s*", "", line).strip()
        ins = re.sub(r"\.L_[0-9A-Fa-f]+", lambda m: labels.setdefault(m.group(0), f"L{len(labels)}"), ins)
        ins = re.sub(r'"?@[0-9A-Za-z_$]+"?|\blbl_[0-9A-Fa-f]+|\bjumptable_[0-9A-Fa-f]+|\bgap_\w+|\b\w+\$\d+', "SYM", ins)
        funcs[cur].append(ins)
    return funcs


# ----------------------------------------------------------------- metric ---

REG = re.compile(r"\b([rf](?:[0-9]|[12][0-9]|3[01]))\b")


def split_ins(ins: str):
    if ins == "<label>":
        return "<label>", ins, []
    mn = ins.split()[0]
    regs = REG.findall(ins)
    shape = REG.sub("#", ins)
    return mn, shape, regs


def metric(tgt: list[str], cand: list[str]):
    """-> dict(op, imm, reg, perm, lines, score)"""
    t = [split_ins(i) for i in tgt]
    c = [split_ins(i) for i in cand]
    sm = difflib.SequenceMatcher(None, [x[0] for x in t], [x[0] for x in c], autojunk=False)
    op = imm = reg = 0
    pairs = []
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal":
            pairs += [(t[i1 + k], c[j1 + k]) for k in range(i2 - i1)]
        else:
            op += max(i2 - i1, j2 - j1)
    co = defaultdict(Counter)
    lines = 0
    for a, b in pairs:
        if a[1] != b[1]:
            imm += 1
            lines += 1
            continue
        d = sum(1 for x, y in zip(a[2], b[2]) if x != y)
        reg += d
        lines += 1 if d else 0
        for x, y in zip(a[2], b[2]):
            co[y][x] += 1
    perm = sum(1 for rc, cnt in co.items() if cnt.most_common(1)[0][0] != rc)
    # colour-rank displacement: callee-saved registers are handed out r31, r30, ... in colouring order, so the
    # rank of a role is its register number counted down from 31. Sum |rank in original - rank in ours| per role.
    rank = 0
    for cls in ("r", "f"):
        mp = {rc: cnt.most_common(1)[0][0] for rc, cnt in co.items() if rc[0] == cls and int(rc[1:]) >= 14}
        tregs = sorted({int(x[1:]) for x in mp.values()}, reverse=True)
        cregs = sorted({int(x[1:]) for x in mp}, reverse=True)
        for rc, rt in mp.items():
            rank += abs(tregs.index(int(rt[1:])) - cregs.index(int(rc[1:])))
    lines += op
    if os.environ.get("REGSEARCH_DIFF"):
        # rank by asm_diff's own number (changed lines of a unified diff of the normalised instructions); the default
        # metric is blind to some float-register colourings and can prefer worse variants (DrawPathDOF Lite, 2026-10-29)
        dl = [x for x in difflib.unified_diff(tgt, cand, lineterm="", n=0) if x[:1] in "+-" and x[:3] not in ("+++", "---")]
        return dict(op=op, imm=imm, reg=reg, perm=perm, rank=rank, lines=len(dl), score=round(10 * len(dl) + 0.25 * reg, 1))
    return dict(op=op, imm=imm, reg=reg, perm=perm, rank=rank, lines=lines,
                score=round(50 * op + 10 * imm + 4 * rank + 0.25 * reg, 1))


# ------------------------------------------------------------------ sites ---

class Site:
    """alts[0] is the original. An alt is a list of edits: ('sub', old, new) or ('decl', text)."""

    def __init__(self, name, alts):
        self.name, self.alts = name, alts


INT_FAMILIES = {"u8": ["u8", "u32"], "u16": ["u16", "u32", "s32"], "u32": ["u32", "s32"], "s32": ["s32", "u32"],
                "int": ["int", "u32"]}
BARE = re.compile(r"^(\s{8,})((?:u8|u16|u32|s32|int|bool|f32|s64|u64)\*?|[A-Za-z_][\w:<>]*\*)\s+(\w+);\s*$")
DECL = re.compile(r"^(\s*)((?:u8|u16|u32|s32|int|bool|f32)\*?|[A-Za-z_][\w:<>]*\*)\s+(\w+)\s*=\s*(.+);\s*$")
SIMPLE = re.compile(r"^\s*[^{}/]*;\s*$")
IDENT = re.compile(r"\b[a-z_]\w*\b")


CALL = re.compile(r"\b(?!static_cast|reinterpret_cast|const_cast|sizeof)\w+\s*\(")
TYPES = r"(?:u8|u16|u32|s8|s16|s32|s64|u64|int|bool|f32|f64)\*?"
PUREDECL = re.compile(r"^\s*(?:" + TYPES + r"|[A-Za-z_][\w:<>]*\*)\s+(\w+)\s*(?:=\s*(.+))?;\s*$")
PUREASG = re.compile(r"^\s*(\w+)\s*=\s*(.+);\s*$")


def pure_info(line):
    """set of names written if the line is a pure decl/assignment (no calls, no stores), else None."""
    m = PUREDECL.match(line) or PUREASG.match(line)
    if not m:
        return None
    expr = m.group(2) if m.lastindex and m.lastindex >= 2 else ""
    if expr and (CALL.search(expr) or "++" in expr or "--" in expr or "=" in expr):
        return None
    return {m.group(1)}


def function_span(lines, fn_hint):
    start = next(i for i, l in enumerate(lines) if re.match(r"^\S.*\b" + re.escape(fn_hint) + r"\s*\(", l) and "{" in l)
    depth, end = 0, None
    for i in range(start, len(lines)):
        depth += lines[i].count("{") - lines[i].count("}")
        if depth == 0:
            end = i
            break
    return start, end


def generic_sites(lines, span):
    start, end = span
    sites = []
    for i in range(start + 1, end):
        mb = BARE.match(lines[i])
        if mb:  # block-scope bare declaration: move it to the top of the function
            sites.append(Site(f"hoistbare:{mb.group(3)}@{i}", [[], [("sub", lines[i] + "\n", ""), ("decl", f"{mb.group(2)} {mb.group(3)};")]]))
            continue
        m = DECL.match(lines[i])
        if not m:
            continue
        ind, ty, name, expr = m.groups()
        if "(" in expr and "static_cast" not in expr and "reinterpret_cast" not in expr:
            continue
        # hoist: declare at the top, assign in place
        hoist = [("sub", lines[i], f"{ind}{name} = {expr};"), ("decl", f"{ty} {name};")]
        sites.append(Site(f"hoist:{name}@{i}", [[], hoist]))
        if ty in INT_FAMILIES:
            alts = [[]] + [[("sub", lines[i], lines[i].replace(ty, t, 1))] for t in INT_FAMILIES[ty][1:]]
            sites.append(Site(f"type:{name}@{i}", alts))
    for i in range(start + 1, end - 1):
        a, b = lines[i], lines[i + 1]
        if a == b or len(a) - len(a.lstrip()) != len(b) - len(b.lstrip()):
            continue
        if not (SIMPLE.match(a) and SIMPLE.match(b)):
            continue
        pa, pb = pure_info(a), pure_info(b)
        ia, ib = set(IDENT.findall(a)), set(IDENT.findall(b))
        if pa is not None and pb is not None:
            wa, wb = pa, pb
            if (wa & ib) or (wb & ia) or (wa & wb):
                continue
        else:
            if ia & ib or DECL.match(a) or DECL.match(b):
                continue
        sites.append(Site(f"swap@{i}", [[], [("sub", a + "\n" + b, b + "\n" + a)]]))
    return sites


def render(base: str, sites, vec, fn_hint: str, order_seed: int):
    text = base
    decls = []
    renames = []
    for s, v in zip(sites, vec):
        for e in s.alts[v]:
            if e[0] == "rename":
                renames.append(e)
            elif e[0] in ("sub", "suball"):
                if text.count(e[1]) < 1:
                    return None
                text = text.replace(e[1], e[2], 1 if e[0] == "sub" else -1)
            else:
                decls.append(e[1])
    for _, old, new in renames:
        ls = text.split("\n")
        a, b = function_span(ls, fn_hint)
        pat = re.compile(r"\b" + re.escape(old) + r"\b")
        ls[a + 1:b + 1] = [pat.sub(new, l) for l in ls[a + 1:b + 1]]
        text = "\n".join(ls)
    if decls:
        random.Random(order_seed).shuffle(decls) if order_seed else None
        lines = text.split("\n")
        start, _ = function_span(lines, fn_hint)
        lines[start + 1:start + 1] = ["    " + d for d in decls]
        text = "\n".join(lines)
    return text


# ---------------------------------------------------------------- evaluate ---

class Evaluator:
    def __init__(self, unit, fn, workdir: Path):
        self.unit, self.fn_hint = unit, fn
        self.work = workdir
        self.work.mkdir(parents=True, exist_ok=True)
        self.tmpl = compile_template(unit)
        self.src = unit_source(unit)
        self.ext = self.src.suffix
        tgt = functions(ROOT / "build" / VERSION / "obj" / f"{unit}.o", self.work)
        self.fname = next(n for n in tgt if fn in n)
        self.tgt = tgt[self.fname]
        self.cache = {}
        self.lock = threading.Lock()
        self.inflight = {}

    def score_text(self, text, tag: str = ""):
        if text is None:
            return dict(score=10**9, op=-1, imm=-1, reg=-1, perm=-1, rank=-1, lines=-1, err="conflicting sites", hash="none")
        h = hashlib.sha1(text.encode()).hexdigest()[:12]
        with self.lock:
            if h in self.cache:
                return self.cache[h]
            ev = self.inflight.get(h)
            mine = ev is None
            if mine:
                self.inflight[h] = threading.Event()
        if not mine:
            ev.wait()
            return self.cache[h]
        try:
            return self._score_text(text, h)
        finally:
            with self.lock:
                self.inflight.pop(h).set()

    def _score_text(self, text: str, h: str):
        p = ROOT / "build" / "search" / f"{self.unit.replace('/', '_')}_{h}{self.ext}"
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(text)
        od = self.work / f"o_{h}"
        obj, log = compile_variant(self.tmpl, p, od)
        if obj is None:
            res = dict(score=10**9, op=-1, imm=-1, reg=-1, perm=-1, rank=-1, lines=-1, err=log[-200:], hash=h)
        else:
            f = functions(obj, od)
            cand = next((v for k, v in f.items() if k == self.fname), None)
            res = dict(metric(self.tgt, cand), hash=h) if cand is not None else dict(
                score=10**9, op=-1, imm=-1, reg=-1, perm=-1, rank=-1, lines=-1, err="function missing", hash=h)
            for q in od.glob("*"):
                q.unlink()
            od.rmdir()
        p.unlink(missing_ok=True)
        self.cache[h] = res
        return res


# ------------------------------------------------------------------ search ---

def fmt(r):
    return f"score={r['score']} op={r['op']} imm={r['imm']} reg={r['reg']} rank={r.get('rank')} perm={r['perm']} lines={r['lines']}"


def search(ev: Evaluator, base: str, sites, jobs: int, minutes: float, out: Path, seed: int, fn_hint: str, temp: float = 12.0):
    rng = random.Random(seed)
    n = len(sites)
    zero = [0] * n
    cur, cur_seed = zero, 0
    best_cur = ev.score_text(render(base, sites, cur, fn_hint, cur_seed))
    print(f"base: {fmt(best_cur)}  sites={n}", flush=True)
    archive = [(best_cur["score"], cur, cur_seed, best_cur)]
    t0, gen, seen, stale = time.time(), 0, set(), 0
    out.mkdir(parents=True, exist_ok=True)
    best_overall = (best_cur["score"], cur, cur_seed)
    with ThreadPoolExecutor(jobs) as ex:
        while time.time() - t0 < minutes * 60 and best_overall[0] > 0:
            gen += 1
            cands = []
            for _ in range(jobs * 2):
                v, sd = list(cur), cur_seed
                for _ in range(rng.choice((1, 1, 2, 3))):
                    k = rng.randrange(n + 1)
                    if k == n:
                        sd = rng.randrange(1, 10**6)
                    else:
                        v[k] = rng.randrange(len(sites[k].alts))
                key = (tuple(v), sd)
                if key in seen:
                    continue
                seen.add(key)
                cands.append((v, sd))
            if not cands:
                stale += 1
                if stale > 200:
                    print("space exhausted")
                    break
                continue
            stale = 0
            res = list(ex.map(lambda c: ev.score_text(render(base, sites, c[0], fn_hint, c[1])), cands))
            for (v, sd), r in zip(cands, res):
                archive.append((r["score"], v, sd, r))
                if r["score"] < best_overall[0]:
                    best_overall = (r["score"], v, sd)
                    txt = render(base, sites, v, fn_hint, sd)
                    (out / "best.txt").write_text(txt)
                    chosen = [s.name + f"={x}" for s, x in zip(sites, v) if x]
                    print(f"[{gen} {int(time.time()-t0)}s] NEW BEST {fmt(r)} sd={sd} {chosen}", flush=True)
            # accept the best candidate if it is not worse (drift on plateaus), else sometimes a random top-5 restart
            res_sorted = sorted(zip(res, cands), key=lambda x: x[0]["score"])
            if res_sorted and res_sorted[0][0]["score"] <= best_cur["score"]:
                best_cur, (cur, cur_seed) = res_sorted[0][0], res_sorted[0][1]
            elif res_sorted and res_sorted[0][0]["score"] < 10**8 and rng.random() < math.exp(
                    -(res_sorted[0][0]["score"] - best_cur["score"]) / temp):
                best_cur, (cur, cur_seed) = res_sorted[0][0], res_sorted[0][1]
            elif gen % 8 == 0:
                archive.sort(key=lambda x: x[0])
                pick = rng.choice(archive[:5])
                best_cur, cur, cur_seed = pick[3], pick[1], pick[2]
            if gen % 10 == 0:
                print(f"[{gen} {int(time.time()-t0)}s] cur={best_cur['score']} best={best_overall[0]} evals={len(ev.cache)}",
                      flush=True)
    archive.sort(key=lambda x: x[0])
    print(f"done: gen={gen} evals={len(ev.cache)} best={best_overall[0]}")
    if best_overall[0] < zero_score(best_cur, archive):
        pass
    return best_overall, archive


def zero_score(best_cur, archive):
    return 10**9


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("mode", choices=["score", "search"])
    ap.add_argument("unit")
    ap.add_argument("function")
    ap.add_argument("--src")
    ap.add_argument("--sites")
    ap.add_argument("--generic", action="store_true")
    ap.add_argument("-j", "--jobs", type=int, default=4)
    ap.add_argument("--minutes", type=float, default=10)
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--temp", type=float, default=12.0)
    ap.add_argument("--out", default=None)
    ap.add_argument("--fn-hint", default=None, help="source-level function name for span detection (default: function)")
    a = ap.parse_args()
    src = Path(a.src) if a.src else unit_source(a.unit)
    base = src.read_text()
    out = Path(a.out) if a.out else ROOT / "build" / "search" / ("run_" + a.function.replace("/", "_")[:40])
    ev = Evaluator(a.unit, a.function, out / "work")
    if a.mode == "score":
        print(fmt(ev.score_text(base)))
        return
    hint = a.fn_hint or a.function
    sites = []
    lines = base.split("\n")
    if a.sites:
        for s in json.loads(Path(a.sites).read_text()):
            alts = [[("sub", *e["sub"]) if "sub" in e else (("suball", *e["suball"]) if "suball" in e else (("rename", *e["rename"]) if "rename" in e else ("decl", e["decl"]))) for e in alt] for alt in s["alts"]]
            sites.append(Site(s["name"], [[]] + alts))
    if a.generic:
        sites += generic_sites(lines, function_span(lines, hint))
    best, archive = search(ev, base, sites, a.jobs, a.minutes, out, a.seed, hint, a.temp)
    print("top:")
    for sc, v, sd, r in archive[:5]:
        print(" ", fmt(r), [s.name + f"={x}" for s, x in zip(sites, v) if x], "seed", sd)


if __name__ == "__main__":
    main()
