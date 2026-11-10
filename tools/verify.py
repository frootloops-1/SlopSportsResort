#!/usr/bin/env python3
"""One-line verification of a single object against the original.

Builds the object, diffs it with objdiff-cli, compares per-function scores to a
saved baseline, and prints a compact result. Run from the repo root.

  python3 tools/verify.py RPTnsScene_unsplit --save      # capture baseline
  python3 tools/verify.py RPTnsScene_unsplit              # build + compare
  python3 tools/verify.py RPTnsScene_unsplit -v           # list changed fns

Exit status: 0 no regressions, 1 regressions, 2 build/diff/lookup failure.
Baselines live in build/evidence/baselines/ (untracked). Only code symbols are
scored; data, relocations and layout are NOT covered, so an all-100% result is
necessary but not sufficient for marking an object Matching.
"""
import argparse
import json
import subprocess
import sys
import tempfile
from pathlib import Path

OBJDIFF = Path("build/tools/objdiff-cli")
BASELINES = Path("build/evidence/baselines")


def fail(msg: str):
    print(msg, file=sys.stderr)
    sys.exit(2)


def find_unit(query: str) -> dict:
    units = json.loads(Path("objdiff.json").read_text())["units"]
    exact = [u for u in units if u["name"].removeprefix("main/").split("/")[-1] == query
             or u["name"].removeprefix("main/") == query]
    hits = exact or [u for u in units if query in u["name"]]
    if not hits:
        fail(f"verify: no unit matches '{query}'")
    if len(hits) > 1:
        names = ", ".join(u["name"].removeprefix("main/") for u in hits[:8])
        fail(f"verify: {len(hits)} units match '{query}': {names}")
    return hits[0]


def run(cmd: list[str]) -> subprocess.CompletedProcess:
    return subprocess.run(cmd, capture_output=True, text=True)


def score(unit: dict) -> dict[str, float]:
    """Per-function match percent from the target side; missing functions count 0."""
    with tempfile.TemporaryDirectory() as tmp:
        out = Path(tmp) / "diff.json"
        r = run([str(OBJDIFF), "diff", "-1", unit["target_path"], "-2", unit["base_path"],
                 "-o", str(out), "--format", "json"])
        if r.returncode != 0 or not out.exists():
            print(r.stdout[-800:] + r.stderr[-800:], file=sys.stderr)
            sys.exit(2)
        data = json.loads(out.read_text())
    scores, sizes = {}, {}
    for s in data["left"]["symbols"]:
        # objdiff-cli 3.6 JSON has no "kind"; functions are the symbols that carry instructions
        if s.get("kind") == "SYMBOL_FUNCTION" or ("kind" not in s and "instructions" in s):
            scores[s["name"]] = float(s.get("match_percent", 0.0))
            sizes[s["name"]] = int(s.get("size", 0))
    return {n: (scores[n], sizes[n]) for n in scores}


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("unit", help="object name or unique substring, e.g. RPSysFontManager")
    ap.add_argument("--save", action="store_true", help="store this result as the baseline")
    ap.add_argument("--no-build", action="store_true", help="skip ninja, diff existing .o")
    ap.add_argument("-v", "--verbose", action="store_true", help="list improved/regressed functions")
    a = ap.parse_args()

    unit = find_unit(a.unit)
    short = unit["name"].removeprefix("main/")
    if not a.no_build:
        b = run(["ninja", unit["base_path"]])
        if b.returncode != 0:
            print((b.stdout + b.stderr)[-1500:], file=sys.stderr)
            print(f"{short}: BUILD FAILED")
            sys.exit(2)

    cur = score(unit)
    total = sum(sz for _, sz in cur.values()) or 1
    text = sum(p * sz for p, sz in cur.values()) / total
    exact = sum(1 for p, _ in cur.values() if p == 100.0)

    bl_path = BASELINES / (short.replace("/", "__") + ".json")
    base = json.loads(bl_path.read_text()) if bl_path.exists() else None
    improved, regressed = [], []
    if base:
        for n, (p, _) in cur.items():
            old = base.get(n, 0.0)
            if p > old + 1e-6:
                improved.append((n, old, p))
            elif p < old - 1e-6:
                regressed.append((n, old, p))
        b_exact = sum(1 for v in base.values() if v == 100.0)
        delta = f" ({exact - b_exact:+d} vs baseline)"
    else:
        delta = " (no baseline; use --save)"

    status = "MATCH-CANDIDATE" if exact == len(cur) else "not a full match"
    print(f"{short}: {exact}/{len(cur)} fns exact{delta}, .text~{text:.2f}% size-weighted, "
          f"+{len(improved)} improved, -{len(regressed)} regressed, {status}")
    if a.verbose or regressed:
        for tag, rows in (("REGRESSED", regressed), ("improved", improved)):
            for n, old, p in rows:
                print(f"  {tag:9} {n} {old:.1f} -> {p:.1f}")
    if a.save:
        bl_path.parent.mkdir(parents=True, exist_ok=True)
        bl_path.write_text(json.dumps({n: p for n, (p, _) in cur.items()}))
        print(f"  baseline saved: {bl_path}")
    sys.exit(1 if regressed else 0)


if __name__ == "__main__":
    main()
