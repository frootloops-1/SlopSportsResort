#!/usr/bin/env python3
"""Per-register live ranges and spill-cost features for target vs ours, to see the colouring order.

MWCC colours callee-saved values in an order driven by (weighted uses, defs, degree). For one function this
prints, for each callee-saved GPR/FPR in the ORIGINAL (r31 coloured first) and the register that plays the
same role in OURS (matched by instruction alignment), the features that feed the spill/colour order:

    first-def .. last-use (instruction index), static uses/defs, loop-weighted uses, degree, calls crossed,
    cost = flow_weight*(2*uses+defs)/degree      (docs/forecast-regalloc-notes.md)

    python3 tools/regroles.py <unit> <function> [--ours FILE.o]

Approximations: dest = first operand for ALU/load, all registers are uses for stores/compares; loop depth
from backward branches; only r14-r31 / f14-f31 are reported.
"""
from __future__ import annotations

import argparse
import difflib
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import regsearch as rs  # noqa: E402

ROOT = rs.ROOT
STORE = re.compile(r"^(st[bhw]|stfs|stfd|stmw|psq_st)u?x?$")
NODEST = re.compile(r"^(cmp|fcmp|b|mt|mf|bl|blr|bctr|bctrl|crxor|twi|tw|sync|dcb|icb|nop|psq_st|st)")
REGX = re.compile(r"\b([rf])(\d+)\b")


def parse(funcs_lines):
    ins = []
    for i, l in enumerate(funcs_lines):
        if l == "<label>":
            ins.append(("<label>", [], []))
            continue
        mn = l.split()[0]
        regs = [(m.group(1), int(m.group(2))) for m in REGX.finditer(l)]
        tgt = re.search(r"(L\d+)\s*$", l)
        d, u = [], []
        if STORE.match(mn) or mn.startswith(("cmp", "fcmp")) or mn in ("blr", "bl", "bctr", "b", "mtctr", "mtlr"):
            u = regs
            if mn.endswith("u") or mn.endswith("ux"):
                d = regs[-1:]
        elif mn.startswith("b"):
            u = regs
        elif regs:
            d, u = regs[:1], regs[1:]
            if mn in ("rlwimi",):  # dest is also a source
                u = regs
        ins.append((mn, d, u, tgt.group(1) if tgt else None) if False else (mn, d, u))
    return ins


def loop_depths(lines):
    """depth per instruction index from backward branches (label defined earlier than the branch)."""
    lab = {}
    for i, l in enumerate(lines):
        if l == "<label>":
            lab.setdefault(i, i)
    # labels are anonymous after normalisation; use the raw text order: a branch to Lk where Lk was
    # introduced at index <= i. Our normaliser numbers labels in first-appearance order, so a branch
    # to a label already seen (introduced earlier by a branch) and followed by '<label>' placement is
    # ambiguous; instead recover with the real label positions below.
    return None


def analyse(obj: Path, fname: str, scratch: Path):
    s = scratch / (obj.parent.name + "_" + obj.stem + "_roles.s")
    import subprocess
    subprocess.run([str(rs.DTK), "elf", "disasm", str(obj), str(s)], check=True, capture_output=True, cwd=ROOT)
    raw, cur = [], None
    for line in s.read_text().splitlines():
        m = re.match(r"\.fn (\S+),", line)
        if m:
            cur = m.group(1)
            continue
        if line.startswith(".endfn"):
            cur = None
            continue
        if cur == fname:
            raw.append(line)
    # instruction list with real label positions
    insns, labpos = [], {}
    for line in raw:
        lm = re.match(r"(\.L_[0-9A-Fa-f]+):", line)
        if lm:
            labpos[lm.group(1)] = len(insns)
            continue
        if not line.startswith("/*"):
            continue
        text = re.sub(r"^/\*.*?\*/\s*", "", line).strip()
        insns.append(text)
    depth = [0] * len(insns)
    for i, t in enumerate(insns):
        m = re.search(r"(\.L_[0-9A-Fa-f]+)", t)
        if m and t.split()[0].startswith("b") and m.group(1) in labpos and labpos[m.group(1)] <= i:
            for k in range(labpos[m.group(1)], i + 1):
                depth[k] += 1
    return insns, depth


def features(insns, depth):
    parsed = parse([re.sub(r"\.L_[0-9A-Fa-f]+", "L", t) for t in insns])
    first_def, last_use = {}, {}
    uses, defs, wuses, key2 = Counter(), Counter(), Counter(), Counter()
    for i, (mn, d, u) in enumerate(parsed):
        w = 8 ** min(depth[i], 3)
        for r in u:
            if r[1] >= 14:
                last_use[r] = i
                first_def.setdefault(r, i)
                uses[r] += 1
                wuses[r] += w
                key2[r] += 2 * w
        for r in d:
            if r[1] >= 14:
                first_def.setdefault(r, i)
                last_use[r] = max(last_use.get(r, i), i)
                defs[r] += 1
                wuses[r] += w
                key2[r] += w
    # extend to loop ends for values defined before a loop and used in it
    calls = [i for i, (mn, _, _) in enumerate(parsed) if mn in ("bl", "bctrl")]
    feat = {}
    for r in first_def:
        lo, hi = first_def[r], last_use[r]
        feat[r] = dict(k2=key2[r], lo=lo, hi=hi, uses=uses[r], defs=defs[r], w=wuses[r], calls=sum(1 for c in calls if lo < c < hi))
    for r, f in feat.items():
        f["deg"] = sum(1 for q, g in feat.items() if q != r and g["lo"] <= f["hi"] and f["lo"] <= g["hi"])
        f["cost"] = round(f["w"] * 2 / max(f["deg"], 1), 1)
    return feat, parsed


def roles(tfeat, tparsed, tl, cparsed, cl):
    sm = difflib.SequenceMatcher(None, [p[0] for p in tparsed], [p[0] for p in cparsed], autojunk=False)
    co = defaultdict(Counter)
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag != "equal":
            continue
        for k in range(i2 - i1):
            for a, b in zip(tparsed[i1 + k][1] + tparsed[i1 + k][2], cparsed[j1 + k][1] + cparsed[j1 + k][2]):
                if a[0] == b[0] and a[1] >= 14:
                    co[a][b] += 1
    return {a: c.most_common(1)[0][0] for a, c in co.items()}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("unit")
    ap.add_argument("function")
    ap.add_argument("--ours")
    a = ap.parse_args()
    scratch = ROOT / "build" / "search" / "roles"
    scratch.mkdir(parents=True, exist_ok=True)
    tobj = ROOT / "build" / rs.VERSION / "obj" / f"{a.unit}.o"
    oobj = Path(a.ours) if a.ours else ROOT / "build" / rs.VERSION / "src" / f"{a.unit}.o"
    names = rs.functions(tobj, scratch)
    fname = next(n for n in names if a.function in n)
    ti, td = analyse(tobj, fname, scratch)
    ci, cd = analyse(oobj, fname, scratch)
    tf, tp = features(ti, td)
    cf, cp = features(ci, cd)
    m = roles(tf, tp, ti, cp, ci)
    fmtf = lambda f: f"{f['lo']:>4}-{f['hi']:<4} u{f['uses']:<3} d{f['defs']:<2} w{f['w']:<5} deg{f['deg']:<3} calls{f['calls']:<2} cost{f['cost']} k{f['k2']}"
    print(f"{fname}\n  target reg  role-feature                                         ours reg  ours feature")
    for r in sorted(tf, key=lambda x: (x[0], -x[1])):
        o = m.get(r)
        print(f"  {r[0]}{r[1]:<3}      {fmtf(tf[r]):<56} {('%s%d' % o) if o else '-':<8}  {fmtf(cf[o]) if o in cf else ''}")


if __name__ == "__main__":
    main()
