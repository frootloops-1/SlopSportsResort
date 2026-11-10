#!/usr/bin/env python3
"""Merge `unk/sinit_*` units whose .text is a single function (just the __sinit) into the named,
non-Matching unit that ends exactly where they start: the __sinit is that unit's last function.
All of the unk unit's sections move to the named unit when adjacent there too; otherwise kept
as separate ranges of the named unit. Usage: merge_sinit_only.py [--apply]"""
import json, re, sys
sys.path.insert(0, 'tools')
from apply_ogws import parse_splits
from sig_match import symbols
P = 'config/RZTE01_01/splits.txt'
sp = parse_splits(P)
FROZEN = {p['name'] for p in json.load(open('config/RZTE01_01/ported_objects.json'))} | {
    'revolution/BTE/stack/hcic/hcicmds.c', 'Pack/RPGraphics/RPGrpDrawPathShadowTexture.cpp', 'runtime/__init_cpp_exceptions.cpp'}
F = [s for s in symbols('config/RZTE01_01/symbols.txt') if s['func']]
ends = {}
for u, v in sp.items():
    for sec, s, e in v:
        if sec == '.text': ends[e] = u
merges = []
for u, v in sp.items():
    if not u.startswith('unk/'): continue
    t = next(x for x in v if x[0] == '.text')
    if sum(1 for f in F if t[1] <= f['addr'] < t[2]) != 1: continue
    prev = ends.get(t[1])
    if prev and not prev.startswith('unk/') and prev not in FROZEN: merges.append((u, prev))
print(f'{len(merges)} merges', merges[:6])
if '--apply' in sys.argv:
    txt = open(P).read()
    for u, prev in merges:
        blk = re.search(rf'(?m)^{re.escape(u)}:\n((?:\t.*\n)+)', txt)
        txt = txt.replace(blk.group(0), '')
        pb = re.search(rf'(?m)^{re.escape(prev)}:\n((?:\t.*\n)+)', txt)
        lines = pb.group(1).splitlines(keepends=True)
        merged = {}
        for l in lines + blk.group(1).splitlines(keepends=True):
            m = re.match(r'\t(\S+)\s+start:0x(\w+) end:0x(\w+)(.*)', l)
            sec, s, e, rest = m.group(1), int(m.group(2), 16), int(m.group(3), 16), m.group(4)
            if sec in merged and merged[sec][-1][1] == s: merged[sec][-1][1] = e
            else: merged.setdefault(sec, []).append([s, e, rest])
        out = ''.join(f'\t{sec:<11} start:0x{s:08X} end:0x{e:08X}{r}\n' for sec, rs in merged.items() for s, e, r in rs)
        txt = txt.replace(pb.group(0), f'{prev}:\n{out}')
    open(P, 'w').write(txt)
