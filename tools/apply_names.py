#!/usr/bin/env python3
"""Rename generic dtk functions from a match JSON (src name -> dst_addr). Usage: apply_names.py JSON SYMBOLS"""
import json, re, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import symbols, GENERIC
m = json.load(open(sys.argv[1])); sym = sys.argv[2]
taken = {s['name'] for s in symbols(sym)}
ren = {}
for r in m:
    if GENERIC.match(r['src']) or r['src'] in taken: continue
    ren[int(r['dst_addr'], 16)] = r['src']; taken.add(r['src'])
lines = open(sym).read().split('\n'); n = 0
for i, l in enumerate(lines):
    mm = re.match(r'^(\S+) = \.text:0x([0-9A-Fa-f]+);', l)
    if mm and GENERIC.match(mm.group(1)) and int(mm.group(2), 16) in ren:
        lines[i] = ren[int(mm.group(2), 16)] + l[len(mm.group(1)):]; n += 1
open(sym, 'w').write('\n'.join(lines)); print(f'renamed {n}')
