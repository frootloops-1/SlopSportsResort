#!/usr/bin/env python3
"""Set each ported unit's .text end to the end of its last function (drop trailing padding, which
belongs to the next unit's alignment). Usage: trim_text_ends.py CONFIG_DIR PORTED_JSON"""
import json, re, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import symbols
cfg, pj = sys.argv[1:3]
units = {p['name'] for p in json.load(open(pj))}
fns = sorted((s['addr'], s['addr'] + s['size']) for s in symbols(f'{cfg}/symbols.txt') if s['func'])
L = open(f'{cfg}/splits.txt').read().split('\n'); cur = None; n = 0
for i, l in enumerate(L):
    if l and not l.startswith('\t') and l.endswith(':'): cur = l[:-1]; continue
    m = re.match(r'\t\.text(\s+)start:0x(\w+) end:0x(\w+)(.*)', l)
    if m and cur in units:
        s, e = int(m.group(2), 16), int(m.group(3), 16)
        last = max(fe for fs, fe in fns if s <= fs < e)
        if last != e: L[i] = f'\t.text{m.group(1)}start:0x{s:08X} end:0x{last:08X}{m.group(4)}'; n += 1
open(f'{cfg}/splits.txt', 'w').write('\n'.join(L)); print(f'trimmed {n}')
