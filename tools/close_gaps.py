#!/usr/bin/env python3
"""Give symbol-free gaps (< 0x20 bytes) between consecutive splits of a section to the earlier split.
Usage: close_gaps.py CONFIG_DIR"""
import re, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import symbols
cfg = sys.argv[1]
starts = {}
for s in symbols(f'{cfg}/symbols.txt'): starts.setdefault(s['sec'], set()).add(s['addr'])
L = open(f'{cfg}/splits.txt').read().split('\n')
ent = []                                    # (sec, start, end, line index)
for i, l in enumerate(L):
    m = re.match(r'\t(\S+)\s+start:0x(\w+) end:0x(\w+)', l)
    if m: ent.append((m.group(1), int(m.group(2), 16), int(m.group(3), 16), i))
by = {}
for e in ent: by.setdefault(e[0], []).append(e)
n = 0
for sec, lst in by.items():
    if sec == '.text': continue
    lst.sort(key=lambda e: e[1])
    for (s0, a0, e0, i0), (s1, a1, e1, i1) in zip(lst, lst[1:]):
        if 0 < a1 - e0 < 0x20 and not any(e0 <= x < a1 for x in starts.get(sec, ())):
            L[i0] = re.sub(r'end:0x\w+', f'end:0x{a1:08X}', L[i0]); n += 1
open(f'{cfg}/splits.txt', 'w').write('\n'.join(L)); print(f'closed {n} gaps')
