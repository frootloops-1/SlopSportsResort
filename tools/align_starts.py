#!/usr/bin/env python3
"""Make data ranges added since BASE start at the alignment their contents need (max symbol
`align:`, 8 for doubles). Extend the start down over unclaimed bytes, otherwise drop the range.
Usage: align_starts.py BASE_SPLITS"""
import re, sys
sys.path.insert(0, 'tools')
from apply_ogws import parse_splits
from sig_match import symbols
base = parse_splits(sys.argv[1]); P = 'config/RZTE01_01/splits.txt'
syms = [s for s in symbols('config/RZTE01_01/symbols.txt') if s['sec'] not in ('.text', '.init')]
def need(sec, s, e):
    al = 4
    for x in syms:
        if x['sec'] == sec and s <= x['addr'] < e:
            m = re.search(r'align:(\d+)', x['attrs']); a = int(m.group(1)) if m else (8 if 'double' in x['attrs'] else 4)
            al = max(al, a)
    return al
sp = parse_splits(P)
claimed = [(sec, s0, e0, u) for u, v in sp.items() for (sec, s0, e0) in v]
L = open(P).read().split('\n'); cur = None; out = []; fixed = dropped = 0
for l in L:
    if l and not l.startswith('\t') and l.endswith(':'): cur = l[:-1]
    m = re.match(r'(\t(\S+)\s+start:0x)(\w+)( end:0x)(\w+)(.*)', l)
    if m and m.group(2) != '.text':
        sec, s, e = m.group(2), int(m.group(3), 16), int(m.group(5), 16)
        if (sec, s, e) not in base.get(cur, []):
            al = need(sec, s, e)
            if s % al:
                s2 = s - s % al
                if any(c[0] == sec and c[3] != cur and c[1] < s and c[2] > s2 for c in claimed): dropped += 1; continue
                l = f'{m.group(1)}{s2:08X}{m.group(4)}{e:08X}{m.group(6)}'; fixed += 1
    out.append(l)
open(P, 'w').write('\n'.join(out)); print(f'aligned {fixed}, dropped {dropped}')
