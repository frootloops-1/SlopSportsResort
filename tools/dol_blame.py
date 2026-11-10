#!/usr/bin/env python3
"""Diff built vs original DOL and report which split units own the differing bytes.
Usage: dol_blame.py ORIG_DOL BUILT_DOL SPLITS [--ported PORTED_JSON]"""
import collections, json, struct, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import dol_sections, read
from apply_ogws import parse_splits
a, asec = dol_sections(sys.argv[1]); b, bsec = dol_sections(sys.argv[2])
sp = parse_splits(sys.argv[3])
ported = set()
if '--ported' in sys.argv: ported = {p['name'] for p in json.load(open(sys.argv[sys.argv.index('--ported') + 1]))}
if [(x, y) for x, y, _ in asec] != [(x, y) for x, y, _ in bsec]:
    print('section layout differs:'); [print(' ', hex(x[0]), hex(x[1]), '|', hex(y[0]), hex(y[1])) for x, y in zip(asec, bsec) if x[:2] != y[:2]]
ranges = sorted((s, e, u) for u, v in sp.items() for (_, s, e) in v)
blame = collections.Counter(); first = {}
for (addr, size, oa), (_, _, ob) in zip(asec, bsec):
    if not oa: continue
    x, y = a[oa:oa + size], b[ob:ob + size]
    for i in range(0, size, 4):
        if x[i:i + 4] != y[i:i + 4]:
            ad = addr + i; u = next((u for s, e, u in ranges if s <= ad < e), 'auto')
            blame[u] += 1; first.setdefault(u, ad)
for u, n in blame.most_common(25): print(f'{n:6} words  {"P " if u in ported else "  "}{u}  first 0x{first[u]:08X}')
