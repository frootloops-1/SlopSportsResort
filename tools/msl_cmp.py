"""Compare built MSL objects with the original split: sections + non-matching symbols.

  python3 tools/msl_cmp.py arith ansi_files        # builds, diffs, prints a line per unit
Run from the repo root. Reports are saved under build/evidence/msl/.
"""
import json, pathlib, subprocess, sys

out = pathlib.Path("build/evidence/msl"); out.mkdir(parents=True, exist_ok=True)
for u in sys.argv[1:]:
    r = subprocess.run(["ninja", f"build/RZTE01_01/src/MSL/{u}.o"], capture_output=True, text=True)
    if r.returncode:
        err = [l for l in r.stdout.splitlines() if l.startswith("#")][:6]
        print(f"{u}: COMPILE FAIL", *err, sep="\n  "); continue
    j = out / f"{u}.json"
    subprocess.run(["build/tools/objdiff-cli", "diff", "-1", f"build/RZTE01_01/obj/MSL/{u}.o",
                    "-2", f"build/RZTE01_01/src/MSL/{u}.o", "-o", str(j), "--format", "json"],
                   check=True, capture_output=True)
    d = json.load(open(j))
    secs = {s["name"]: round(s.get("match_percent") or 0, 2) for s in d["left"]["sections"] if s["name"].startswith(".") and s.get("match_percent") is not None}
    syms = [s for s in d["left"]["symbols"] if not s["name"].startswith("[") and not s["name"].startswith(".") and (s.get("match_percent") is not None or "instructions" in s)]
    bad = [(s["name"], round(s.get("match_percent") or 0, 1)) for s in syms if s.get("match_percent") != 100]
    # config-type hints: data symbols whose size differs between sides (padding in symbols.txt)
    rs = {x["name"]: x for x in d["right"]["symbols"]}
    sz = [f'{x["name"]} {x.get("size")}!={rs[x["name"]].get("size")}' for x in d["left"]["symbols"]
          if x["name"] in rs and x.get("size") != rs[x["name"]].get("size") and not x["name"].startswith("[")]
    gaps = [x["name"] for x in d["left"]["symbols"] if x["name"].startswith("gap_")]
    hint = (f"; SIZE-MISMATCH {sz[:6]}" if sz else "") + (f"; gap symbols {gaps[:4]}" if gaps else "")
    print(f"{u}: sections {secs}; {len(syms)-len(bad)}/{len(syms)} syms exact; misses {bad[:10]}{hint}")
