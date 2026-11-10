#!/usr/bin/env python3
"""Report units whose .text symbol order differs between the built and target objects.

objdiff matches functions by name, so a unit can score 100% code while the
linked DOL still differs because the compiler emitted functions in another
order (MWCC -inline deferred emits in reverse of source order for some
shapes). Compare `nm -n` order of text symbols; a mismatch means reorder the
definitions in the source.

Only text symbols present in BOTH objects are compared. Our object often has
extra local inline helpers (or lacks functions not yet written); requiring
identical symbol sets silently skipped those units even when the link drifted.

  python3 tools/order_check.py                  # all units with both objects
  python3 tools/order_check.py revolution/VF    # restrict by substring
"""
import re
import subprocess
import sys
from pathlib import Path

NM = "build/binutils/powerpc-eabi-nm"


def text_order(path: Path) -> list[str]:
    out = subprocess.run([NM, "-n", "--defined-only", str(path)], capture_output=True, text=True).stdout
    # nm -n prints "addr type name"; keep text symbols (T/t) only
    return [l.split()[2] for l in out.splitlines() if len(l.split()) == 3 and l.split()[1] in "Tt"]


def main() -> None:
    flt = sys.argv[1] if len(sys.argv) > 1 else ""
    ours_root = Path("build/RZTE01_01/src")
    tgt_root = Path("build/RZTE01_01/obj")
    bad = 0
    for ours in sorted(ours_root.rglob("*.o")):
        rel = ours.relative_to(ours_root)
        if flt not in str(rel):
            continue
        tgt = tgt_root / rel
        if not tgt.exists():
            continue
        a, b = text_order(ours), text_order(tgt)
        common = set(a) & set(b)
        a = [n for n in a if n in common]
        b = [n for n in b if n in common]
        if a == b:
            continue
        bad += 1
        first = next(i for i, (x, y) in enumerate(zip(a, b)) if x != y)
        print(f"{rel.with_suffix('')}: order differs at #{first}: ours {a[first]} / target {b[first]}")
    print(f"{bad} unit(s) with different text order")


if __name__ == "__main__":
    main()
