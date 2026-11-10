#!/usr/bin/env python3
"""Compile one unit with every available MWCC build and score it (read-only except build/<unit>.o).

    python3 tools/version_sweep.py revolution/VF/pf_entry_iterator [--versions 3.0a5 3.0a3.4 ...]

Why: the compiler build is a per-unit input. RVL_SDK code was built with GC/3.0a5 (not 3.0a5.2): pf_cp932 and
pf_entry_iterator only matched after `Object(..., mw_version="GC/3.0a5")`. Run this BEFORE any variant or
permuter search on a unit that is below 100%, and again after each source change (compiler and source interact).
Units built with the SportsPack precompiled header get a per-version header in build/pchv/<version>/.
Run it in a worktree you can rebuild; the unit's object is restored with ninja at the end.
Then set mw_version in configure.py and `python3 configure.py`; the permuter reads it from there.
"""
import argparse, glob, os, re, subprocess, sys
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULT = ["3.0a5.2", "3.0a5", "3.0a3.4", "3.0a3.3", "3.0a3.2", "3.0a3"]

def sh(cmd):
    r = subprocess.run(cmd, shell=True, cwd=ROOT, capture_output=True, text=True)
    return r.returncode, r.stdout + r.stderr

def score(unit):
    _, out = sh(f"python3 tools/verify.py {unit} --no-build 2>&1 | tail -1")
    m = re.search(r"(\d+)/(\d+) fns exact.*?\.text~([\d.]+)%", out)
    return f"{m.group(1)}/{m.group(2)} fns exact, .text {m.group(3)}%" if m else out.strip()[:70]

def pch_for(version, mch_cmd):
    d = f"build/pchv/{version}"
    if not os.path.exists(os.path.join(ROOT, d, "SportsPack.mch")):
        os.makedirs(os.path.join(ROOT, d), exist_ok=True)
        sh(f"cp -R build/RZTE01_01/include/. {d}/")
        c = re.sub(r"compilers/GC/[\w.]+/", f"compilers/GC/{version}/", mch_cmd, count=1)
        c = re.sub(r"-o \S+include\b", f"-o {ROOT}/{d}", c)
        sh(c)
    return d

def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("unit", help="objdiff unit path, e.g. revolution/VF/pf_cp932")
    ap.add_argument("--versions", nargs="*", default=DEFAULT)
    a = ap.parse_args()
    srcs = glob.glob(f"{ROOT}/src/{a.unit}.*")
    if not srcs:
        sys.exit("no source for unit")
    obj = "build/RZTE01_01/" + os.path.splitext(os.path.relpath(srcs[0], ROOT))[0] + ".o"
    _, cmd = sh(f"ninja -t commands {obj} | tail -1")
    base = cmd.split(" && ")[0].strip()
    cur = re.search(r"compilers/GC/([\w.]+)/", base).group(1)
    uses_pch = "SportsPack.mch" in base
    mch_cmd = None
    if uses_pch:
        _, mch_cmd = sh(f"ninja -t commands {ROOT}/build/RZTE01_01/include/SportsPack.mch | tail -1")
        mch_cmd = mch_cmd.split(" && ")[0].strip()
    print(f"## {a.unit} (configured compiler {cur})")
    try:
        for v in a.versions:
            c = re.sub(r"compilers/GC/[\w.]+/", f"compilers/GC/{v}/", base, count=1)
            if uses_pch:
                c = c.replace("-i build/RZTE01_01/include", f"-i {pch_for(v, mch_cmd)}")
            rc, out = sh(c)
            print(f"  {v:8s} {'COMPILE FAIL' if rc or 'Error' in out else score(a.unit)}" + ("  <- configured" if v == cur else ""))
    finally:
        sh(f"touch src/{os.path.relpath(srcs[0], ROOT + '/src')} && ninja {obj}")

if __name__ == "__main__":
    main()
