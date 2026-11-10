#!/usr/bin/env python3
"""Group every near-miss function and every inexact-data unit by the tooling
that is most likely to close it.

Reads a built checkout (default: cwd, never builds) with the same inputs as
tools/near_miss.py. Each near-miss function gets exactly one function group
(F1..F9, first matching rule wins); each unit whose data sections are inexact
and which has no near-miss function gets one data group (D1..D5).

  python3 tools/near_miss_groups.py                      # counts per group
  python3 tools/near_miss_groups.py --list F3 --limit 30 # easiest first
  python3 tools/near_miss_groups.py --tsv out.tsv        # every row
  python3 tools/near_miss_groups.py --markdown out.md    # doc-ready tables

"flip" counts the units where this function is the only thing keeping the unit
from 100% code, i.e. closing it can flip the object (after the DOL link check).
"""
import argparse
import collections
import json
import os
import re
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import near_miss as nm  # noqa: E402

FN_GROUPS = {
    "F1": ("data-ref: symbols.txt / splits / pool labels (code identical)",
           "near_miss.py --renames, symbols.txt edits, dol_diff.py, sym_addr_check.py; no codegen"),
    "F2": ("prototype / type: return-width, signedness, cast",
           "header edit; hand or Haiku/Sonnet, minutes each"),
    "F3": ("control-flow shape: moved join, switch form, redundant compare",
           "Sonnet batches of ~13 with docs/lessons label-only/branch-shape recipes"),
    "F4": ("immediates: struct offsets, constants",
           "struct/header layout fixes (Ghidra types, other TUs using the struct); Sonnet"),
    "F5": ("stack layout: local declaration order / temps",
           "hand: reorder locals; permuter on declaration order"),
    "F6": ("argument-setup order (SCHEDULE +args)",
           "hand: reorder argument expressions / temporaries; Sonnet"),
    "F7": ("pure register allocation or scheduling",
           "permuter (after C++/inline fixes), register-signature scoring; Opus only if one diff from an object flip"),
    "F8": ("inlining / temp lifetime (nonvolatile count, bl count)",
           "Opus: find the original inline/template boundary; compare sibling TUs"),
    "F9": ("other instruction selection (mr/li, float, branch)",
           "hand with per-function asm_diff; Sonnet then Opus"),
}
DATA_GROUPS = {
    "D1": (".sdata2 only", "float/double pool order and values: literal order, dead consts; dol_diff (objdiff cannot see pool values)"),
    "D2": (".data / .rodata / .sdata only", "tables, vtables, string_table merges, symbol sizes in symbols.txt, splits"),
    "D3": ("several data sections", "usually one shared cause (symbol size/split boundary); fix the first section, re-diff"),
    "D4": ("extab / extabindex", "exception tables: function order, dtor presence, -Cpp_exceptions / pragma; compare a matched sibling"),
}
FN_SHAPE = {"join-moved", "one-case-switch", "double-cond", "extra-cmp", "fewer-cmp",
            "early-return", "loop-ctr", "returns-self"}


def fn_group(f):
    b, s, h = f["bucket"], f["sub"], set(f.get("hints", []))
    if b == "DATA-REF":
        return "F1"
    if "ret-mask" in h or b in ("EXT-CAST", "CMP-SIGN"):
        return "F2"
    if h & FN_SHAPE:
        return "F3"
    if b == "IMM":
        return "F4"
    if b == "STACK-LAYOUT":
        return "F5"
    if b == "SCHEDULE" and s == "+args":
        return "F6"
    if b in ("REGALLOC", "SCHEDULE"):
        return "F7"
    if b in ("NV-REGS", "CALLS"):
        return "F8"
    return "F9"


def data_group(secs):
    names = {n for n, _ in secs}
    if names <= {"extab", "extabindex"}:
        return "D4"
    if names == {".sdata2"}:
        return "D1"
    if len(names) == 1:
        return "D2"
    return "D3"


def matching_units():
    """Units configure.py marks Matching for the target version (RZTE01_01)."""
    out = set()
    for m in re.finditer(r'Object\(\s*(.+?),\s*"([^"]+\.(?:cpp|c|s))"', Path("configure.py").read_text()):
        status, path = m.group(1).strip(), m.group(2)
        if (status in ("Matching", "Equivalent") or status == 'MatchingFor("RZTE01_01")'
                or status == 'not MatchingFor("RSPE01_00")'):
            out.add(re.sub(r"\.(cpp|c|s)$", "", path))
    return out


def unit_scan(args):
    objdiff, unit = args
    d = nm.run_objdiff(objdiff, unit)
    if not d:
        return unit["name"].removeprefix("main/"), None
    secs = [(x["name"], round(float(x.get("match_percent", 100)), 2))
            for x in d["left"].get("sections", [])
            if x.get("kind") == "SECTION_DATA" and float(x.get("match_percent", 100)) < 100]
    return unit["name"].removeprefix("main/"), secs


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--root", default=".")
    ap.add_argument("--list", metavar="GROUP", help="rows of one group (F1..F9, D1..D4), easiest first")
    ap.add_argument("--limit", type=int, default=25)
    ap.add_argument("--skip-tried", action="store_true", help="drop functions with a recorded nogain")
    ap.add_argument("--tsv", metavar="PATH")
    ap.add_argument("--markdown", metavar="PATH")
    ap.add_argument("-j", "--jobs", type=int, default=os.cpu_count() or 4)
    a = ap.parse_args()
    os.chdir(a.root)

    objdiff = "build/tools/objdiff-cli"
    units = json.loads(Path("objdiff.json").read_text())["units"]
    todo = [u for u in units if u.get("base_path") and Path(u["base_path"]).exists()
            and Path(u["target_path"]).exists()]
    with ThreadPoolExecutor(a.jobs) as ex:
        results = list(ex.map(nm.analyze_unit, [(objdiff, u, 0.0, 100.0, 2) for u in todo]))
        secs_by_unit = dict(ex.map(unit_scan, [(objdiff, u) for u in todo]))

    done = matching_units()
    tried = nm.tried_nogain()
    fns = [f for _, _, _, fl, _, _ in results for f in fl]
    per_unit = collections.Counter(f["unit"] for f in fns)
    rows = []
    for f in fns:
        if f["unit"].removeprefix("main/") in done or any(f["unit"].endswith(d.split("/", 1)[-1]) and
                                                           f["unit"] == d.split("/", 1)[-1] for d in done):
            continue
        g = fn_group(f)
        flip = per_unit[f["unit"]] == 1 and not secs_by_unit.get(f["unit"])
        rows.append({"group": g, "unit": f["unit"], "fn": f["sym"], "pct": f["pct"], "wrong": f["wrong"],
                     "size": f["size"], "bucket": f["bucket"], "sub": f["sub"] or "-",
                     "hints": ",".join(f.get("hints", [])) or "-", "flip": flip,
                     "tried": f["sym"] in tried})
    if a.skip_tried:
        rows = [r for r in rows if not r["tried"]]
    for u, secs in secs_by_unit.items():
        if secs and per_unit[u] == 0 and u not in done:
            rows.append({"group": data_group(secs), "unit": u, "fn": ",".join(n for n, _ in secs),
                         "pct": min(p for _, p in secs), "wrong": 0, "size": 0, "bucket": "DATA",
                         "sub": "-", "hints": "-", "flip": True, "tried": False})
    rows.sort(key=lambda r: (r["group"], not r["flip"], r["wrong"], -r["pct"]))

    if a.tsv:
        cols = ["group", "unit", "fn", "pct", "wrong", "size", "bucket", "sub", "hints", "flip", "tried"]
        Path(a.tsv).write_text("\n".join("\t".join(str(r[c]) for c in cols)
                                         for r in [dict(zip(cols, cols))] + rows) + "\n")
    names = {**{k: v for k, v in FN_GROUPS.items()}, **{k: v for k, v in DATA_GROUPS.items()}}
    by = collections.defaultdict(list)
    for r in rows:
        by[r["group"]].append(r)

    if a.list:
        for r in by[a.list][:a.limit]:
            print(f"{r['pct']:6.2f}% wrong={r['wrong']:<3} {'FLIP ' if r['flip'] else '     '}"
                  f"{'tried ' if r['tried'] else ''}{r['bucket']}:{r['sub']} [{r['hints']}] {r['unit']} :: {r['fn'][:70]}")
        return

    def summary(g):
        L = by[g]
        return (len(L), sum(1 for r in L if r["wrong"] <= 4), sum(1 for r in L if r["flip"]),
                sum(1 for r in L if r["tried"]))

    if a.markdown:
        out = ["| Group | What | Tooling | Items | <=4 wrong | Object-flip | Tried-nogain |", "|---|---|---|---:|---:|---:|---:|"]
        for g in sorted(by):
            n, e, fl, t = summary(g)
            out.append(f"| {g} | {names[g][0]} | {names[g][1]} | {n} | {e} | {fl} | {t} |")
        Path(a.markdown).write_text("\n".join(out) + "\n")
    print(f"{'grp':<4}{'items':>6}{'<=4w':>6}{'flip':>6}{'tried':>6}  description")
    for g in sorted(by):
        n, e, fl, t = summary(g)
        print(f"{g:<4}{n:>6}{e:>6}{fl:>6}{t:>6}  {names[g][0]}")


if __name__ == "__main__":
    main()
