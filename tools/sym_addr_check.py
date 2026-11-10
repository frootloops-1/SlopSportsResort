#!/usr/bin/env python3
"""After a failed DOL link, find the first symbol whose linked address differs
from config/<ver>/symbols.txt.  Everything after it is shifted, so the culprit is
the unit just before it (a dropped/extra function, a wrong data size, alignment).

  ninja build/RZTE01_01/main.dol; python3 tools/sym_addr_check.py [N]
"""
import collections
import re
import subprocess
import sys

NM = "build/binutils/powerpc-eabi-nm"
ELF = "build/RZTE01_01/main.elf"
SYMS = "config/RZTE01_01/symbols.txt"


def main() -> None:
    limit = int(sys.argv[1]) if len(sys.argv) > 1 else 8
    out = subprocess.run([NM, ELF], capture_output=True, text=True).stdout
    elf = collections.defaultdict(list)
    for line in out.splitlines():
        p = line.split()
        if len(p) == 3:
            elf[p[2]].append(int(p[0], 16))
    cfg = collections.defaultdict(list)
    for line in open(SYMS):
        m = re.match(r"(\S+) = \.\w+:0x([0-9A-Fa-f]+);", line)
        if m:
            cfg[m.group(1)].append(int(m.group(2), 16))
    bad = sorted(
        (a[0], n, elf[n][0])
        for n, a in cfg.items()
        if len(a) == 1 and len(elf.get(n, [])) == 1 and elf[n][0] != a[0] and a[0] >= 0x80000000 and not n.startswith(("@", "lbl_", "gap_"))
    )
    print(f"{len(bad)} unique symbols at a different address")
    for a, n, e in bad[:limit]:
        print(f"  {a:#x} {n}: linked {e:#x} ({e - a:+d})")


if __name__ == "__main__":
    main()
