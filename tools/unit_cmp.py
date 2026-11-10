"""Section + symbol comparison of a built unit against the original split.

  python3 tools/unit_cmp.py Pack/RPKernel/RPSysParticleManager [...]

Builds the object, runs objdiff, prints section match % and non-exact symbols
(plus size mismatches).  Unlike verify.py this covers data sections.
"""
import json, pathlib, subprocess, sys

out = pathlib.Path("build/evidence/unit_cmp"); out.mkdir(parents=True, exist_ok=True)
for u in sys.argv[1:]:
    r = subprocess.run(["ninja", f"build/RZTE01_01/src/{u}.o"], capture_output=True, text=True)
    if r.returncode:
        print(f"{u}: COMPILE FAIL", *[l for l in r.stdout.splitlines() if l.startswith("#")][:6], sep="\n  "); continue
    j = out / (u.replace("/", "__") + ".json")
    subprocess.run(["build/tools/objdiff-cli", "diff", "-1", f"build/RZTE01_01/obj/{u}.o",
                    "-2", f"build/RZTE01_01/src/{u}.o", "-o", str(j), "--format", "json"],
                   check=True, capture_output=True)
    d = json.load(open(j))
    secs = {s["name"]: round(s.get("match_percent") or 0, 2) for s in d["left"]["sections"]
            if s["name"].startswith(".") and s.get("match_percent") is not None}
    syms = [s for s in d["left"]["symbols"] if not s["name"].startswith("[")
            and not s["name"].startswith(".") and s.get("match_percent") is not None]
    bad = [(s["name"][:40], round(s.get("match_percent") or 0, 1)) for s in syms if s.get("match_percent") != 100]
    rs = {x["name"]: x for x in d["right"]["symbols"]}
    sz = [f'{x["name"][:30]} {x.get("size")}!={rs[x["name"]].get("size")}' for x in d["left"]["symbols"]
          if x["name"] in rs and x.get("size") != rs[x["name"]].get("size") and not x["name"].startswith("[")]
    print(f"{u}: sections {secs}; {len(syms)-len(bad)}/{len(syms)} syms exact; misses {bad[:12]}"
          + (f"; SIZE-MISMATCH {sz[:6]}" if sz else ""))
