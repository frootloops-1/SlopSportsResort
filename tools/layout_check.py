#!/usr/bin/env python3
"""For each ported unit, compare each linked function's offset from the unit's first function with
the original. Prints units whose internal layout differs. Usage: layout_check.py ELF CONFIG_DIR PORTED_JSON"""
import json, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from obj_score import elf
from sig_match import symbols
from apply_ogws import parse_splits
b, secs, syms, _ = elf(sys.argv[1]); cfg = sys.argv[2]
ti = next(i for i, s in enumerate(secs) if s['name'] == '.text')
built = {s['name']: s['value'] for s in syms if s['type'] == 2 and s['shndx'] == ti}
orig = sorted((s['addr'], s['name']) for s in symbols(f'{cfg}/symbols.txt') if s['func'])
sp = parse_splits(f'{cfg}/splits.txt'); bad = []
for p in json.load(open(sys.argv[3])):
    t = next((x for x in sp.get(p['name'], []) if x[0] == '.text'), None)
    if not t: continue
    fs = [(a, n) for a, n in orig if t[1] <= a < t[2] and n in built]
    if not fs: continue
    a0, n0 = fs[0]
    if any(built[n] - built[n0] != a - a0 for a, n in fs): bad.append(p['name'])
print('\n'.join(bad))
