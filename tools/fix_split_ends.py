#!/usr/bin/env python3
"""Extend data-section split ends of the given units so they never end inside a symbol, and round
them up to 4 bytes. Usage: fix_split_ends.py CONFIG_DIR PORTED_JSON"""
import json, re, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import symbols
cfg, pj = sys.argv[1], sys.argv[2]
units = {p['name'] for p in json.load(open(pj))}
syms = [s for s in symbols(f'{cfg}/symbols.txt') if not s['func'] and s['size']]
by_sec = {}
for s in syms: by_sec.setdefault(s['sec'], []).append((s['addr'], s['addr'] + s['size']))
text = open(f'{cfg}/splits.txt').read().split('\n'); cur = None; n = 0
starts = [(m.group(1), int(m.group(2), 16)) for m in (re.match(r'\t(\S+)\s+start:0x(\w+)', l) for l in text) if m]
for i, l in enumerate(text):
    if l and not l.startswith('\t') and l.endswith(':'): cur = l[:-1]; continue
    m = re.match(r'\t(\S+)(\s+)start:0x(\w+) end:0x(\w+)(.*)', l)
    if not m or cur not in units or m.group(1) == '.text': continue
    sec, s, e = m.group(1), int(m.group(3), 16), int(m.group(4), 16)
    e2 = (e + 3) & ~3
    for a, b in by_sec.get(sec, []):
        if a < e2 < b: e2 = b
    nxt = min((s1 for (sec1, s1) in starts if sec1 == sec and s1 >= e2), default=None)
    if nxt is not None and nxt - e2 < 0x20 and not any(e2 <= a < nxt for a, _ in by_sec.get(sec, [])):
        e2 = nxt                                                # swallow symbol-free inter-unit padding
    if e2 != e:
        text[i] = f'\t{sec}{m.group(2)}start:0x{s:08X} end:0x{e2:08X}{m.group(5)}'; n += 1
open(f'{cfg}/splits.txt', 'w').write('\n'.join(text)); print(f'adjusted {n} ends')
