#!/usr/bin/env python3
"""Where does the built main.dol differ from the original? Prints byte count and
the 16-byte-aligned guest addresses of the first differences, then the symbol
containing each (from config symbols.txt).  Run after `ninja build/RZTE01_01/main.dol`.
"""
import re
import struct
import sys
from pathlib import Path

BUILT = Path("build/RZTE01_01/main.dol")
ORIG = Path("orig/RZTE01_01/sys/main.dol")
SYMS = Path("config/RZTE01_01/symbols.txt")


def main() -> None:
    d, o = BUILT.read_bytes(), ORIG.read_bytes()
    off = struct.unpack(">18I", d[0:72])
    addr = struct.unpack(">18I", d[72:144])
    size = struct.unpack(">18I", d[144:216])

    def guest(i: int):
        for s in range(18):
            if size[s] and off[s] <= i < off[s] + size[s]:
                return addr[s] + i - off[s]
        return None

    diffs = [i for i in range(min(len(d), len(o))) if d[i] != o[i]]
    print(f"{len(diffs)} differing byte(s); sizes built {len(d)} orig {len(o)}")
    if not diffs:
        return
    syms = []
    for line in SYMS.read_text().splitlines():
        m = re.match(r"(\S+) = \.\w+:0x([0-9A-Fa-f]+);.*size:0x([0-9A-Fa-f]+)", line)
        if m:
            syms.append((int(m.group(2), 16), int(m.group(3), 16), m.group(1)))
    seen = []
    for i in diffs:
        g = guest(i)
        if g is None:
            continue
        name = next((n for a, s, n in syms if a <= g < a + s), "?")
        if not seen or seen[-1][1] != name:
            seen.append((hex(g), name))
        if len(seen) >= int(sys.argv[1]) if len(sys.argv) > 1 else len(seen) >= 12:
            break
    for g, n in seen:
        print(f"  {g} {n}")


if __name__ == "__main__":
    main()
