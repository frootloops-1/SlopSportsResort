#!/usr/bin/env python3
"""Flip gate for one unit: temporarily make it Matching in configure.py and check the DOL still links byte-exact.

  python3 tools/flip_gate.py <unit> [--keep]      # unit = path under src/ with or without .cpp/.c
                                                  #   e.g. Pack/RPSports/RPBowScene or nw4r/ef/ef_animcurve.cpp

Steps: refuse if configure.py has uncommitted changes; set that unit's Object(NonMatching, ...) to Object(Matching, ...);
`python3 configure.py`; `ninja build/RZTE01_01/main.dol`; tools/dol_diff.py (must be 0 bytes); tools/sym_addr_check.py
(only the known collisions __FUNCTION__$1983, CPUFifo, GPFifo, time$1107 may be at a different address).
Then configure.py is restored (git checkout configure.py + python3 configure.py) unless --keep, even on error/Ctrl-C.
A unit that is already Matching just gets the DOL checks. Last line: FLIP-OK / FLIP-FAIL <reason>; exit 0 only for FLIP-OK.
Run it in a worktree where nothing else is building (ninja is not concurrency-safe).
"""
import re
import subprocess
import sys
from pathlib import Path

KNOWN = {"__FUNCTION__$1983", "CPUFifo", "GPFifo", "time$1107"}
LESSON = "docs/lessons/2026-11-01-flip-gate-short-by-whole-functions-*.md"
DOL = "build/RZTE01_01/main.dol"


def sh(cmd, **kw):
    return subprocess.run(cmd, capture_output=True, text=True, **kw)


def find_unit(text: str, unit: str):
    unit = re.sub(r"\.(cpp|c)$", "", unit.strip().removeprefix("src/"))
    pat = re.compile(r'(Object\(\s*)([^,"]+?)(\s*,\s*"' + re.escape(unit) + r'\.(?:cpp|c)")')
    ms = list(pat.finditer(text))
    return unit, ms


def finish(ok: bool, msg: str, restore) -> None:
    restore()
    print(("FLIP-OK" if ok else "FLIP-FAIL " + msg) + (f" ({msg})" if ok and msg else ""))
    sys.exit(0 if ok else 1)


def main() -> None:
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    keep = "--keep" in sys.argv
    if len(args) != 1:
        sys.exit(__doc__)
    cfg = Path("configure.py")
    if sh(["git", "diff", "--quiet", "--", "configure.py"]).returncode != 0:
        print("FLIP-FAIL configure.py has uncommitted changes; commit or stash them first")
        sys.exit(1)
    text = cfg.read_text()
    unit, ms = find_unit(text, args[0])
    if not ms:
        print(f"FLIP-FAIL unit {unit!r} not found in configure.py")
        sys.exit(1)
    if len(ms) > 1:
        print(f"FLIP-FAIL unit {unit!r} matches {len(ms)} Object() lines in configure.py")
        sys.exit(1)
    m = ms[0]
    if not re.search(r"^" + re.escape(unit) + r"\.(?:cpp|c):", Path("config/RZTE01_01/splits.txt").read_text(), re.M):
        print(f"note: {unit} has no splits.txt entry, so flipping it changes nothing in the link (the gate proves nothing)")
    state = m.group(2).strip()
    changed = False

    def restore():
        if changed and not keep:
            sh(["git", "checkout", "--", "configure.py"])
            r = sh(["python3", "configure.py"])
            print("configure.py restored" + ("" if r.returncode == 0 else " (python3 configure.py FAILED)"))
        elif changed:
            print("--keep: configure.py left with the unit Matching")

    try:
        if state == "Matching":
            print(f"{unit}: already Matching; running the DOL checks only")
        elif state == "NonMatching":
            cfg.write_text(text[: m.start(2)] + "Matching" + text[m.end(2):])
            changed = True
            print(f"{unit}: NonMatching -> Matching (temporary)")
            r = sh(["python3", "configure.py"])
            if r.returncode != 0:
                print((r.stdout + r.stderr)[-400:])
                finish(False, "python3 configure.py failed", restore)
        else:
            finish(False, f"unit state is {state!r}, not a plain NonMatching/Matching", restore)

        r = sh(["ninja", DOL])
        lines = [l for l in (r.stdout + r.stderr).splitlines() if l.strip() and not l.lstrip().startswith("#")]
        print("\n".join(l[:200] for l in lines[-3:]))
        if r.returncode != 0:
            finish(False, "ninja build/RZTE01_01/main.dol failed", restore)

        r = sh(["python3", "tools/dol_diff.py"])
        dl = r.stdout.splitlines()
        print(dl[0] if dl else r.stderr[-200:])
        sm = re.match(r"(\d+) differing byte\(s\); sizes built (\d+) orig (\d+)", dl[0]) if dl else None
        if r.returncode != 0 or not sm:
            finish(False, "dol_diff.py failed to run", restore)
        ndiff, built, orig = map(int, sm.groups())

        r = sh(["python3", "tools/sym_addr_check.py", "60"])
        shifted = re.findall(r"^\s+0x[0-9a-f]+ (\S+): linked", r.stdout, re.M)
        unknown = [s for s in shifted if s not in KNOWN]
        print("sym_addr_check: " + (r.stdout.splitlines()[0] if r.stdout else r.stderr[-200:]))
        for l in r.stdout.splitlines()[1:]:
            tag = "" if l.split()[1].rstrip(":") in KNOWN else "   <-- UNKNOWN"
            print(l[:160] + tag)

        reasons = []
        if ndiff:
            print("\n".join(dl[1:6]))
            reasons.append(f"dol_diff {ndiff} bytes" + (f", built {orig - built} short" if built < orig else ""))
        if unknown:
            reasons.append("unknown shifted symbols: " + " ".join(unknown[:5]))
        if built < orig or unknown:
            print(f"hint: built is {'short' if built < orig else 'different'}/symbols shifted: likely a dead-stripped table or "
                  f"emission-order problem: see {LESSON}")
        if reasons:
            finish(False, "; ".join(reasons), restore)
        finish(True, "dol 0 bytes, only known collisions" + ("; configure.py kept" if keep and changed else ""), restore)
    except KeyboardInterrupt:
        finish(False, "interrupted", restore)
    except SystemExit:
        raise
    except Exception as e:  # always restore
        finish(False, f"internal error {e!r}", restore)


if __name__ == "__main__":
    main()
