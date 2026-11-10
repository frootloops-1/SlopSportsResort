#!/usr/bin/env python3
"""Move a .text boundary when a vtable's own methods sit at the edge of the neighbouring unit.
owner=A, methods in next unit B: if B's functions from its start through the last method are all
either methods of that vtable or unnamed, move the A/B boundary to after the last such function.
owner=B, methods in previous unit A: symmetric, moving the boundary back to the first method.
Usage: vtable_shift.py DOL SYMBOLS [--apply]"""
import bisect, re, struct, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import symbols, dol_sections, read, GENERIC
from apply_ogws import parse_splits
P = 'config/RZTE01_01/splits.txt'
d, ds = dol_sections(sys.argv[1]); S = symbols(sys.argv[2]); sp = parse_splits(P)
F = sorted([s for s in S if s['func'] and s['sec'] == '.text'], key=lambda s: s['addr']); fa = {f['addr']: i for i, f in enumerate(F)}
text = sorted((s, e, u) for u, v in sp.items() for (sec, s, e) in v if sec == '.text'); ts = [t[0] for t in text]
def ti(a):
    i = bisect.bisect_right(ts, a) - 1
    return i if i >= 0 and a < text[i][1] else None
data = sorted((s, e, u) for u, v in sp.items() for (sec, s, e) in v if sec == '.data'); dst = [x[0] for x in data]
def dunit(a):
    i = bisect.bisect_right(dst, a) - 1
    return data[i][2] if i >= 0 and a < data[i][1] else None
ct = read(d, ds, 0x80653FA0, 0x594)
SINIT = {struct.unpack('>I', ct[i:i + 4])[0] for i in range(0, len(ct), 4)}
import json
FROZEN = {p['name'] for p in json.load(open('config/RZTE01_01/ported_objects.json'))} | {
    'revolution/BTE/stack/hcic/hcicmds.c', 'Pack/RPGraphics/RPGrpDrawPathShadowTexture.cpp', 'runtime/__init_cpp_exceptions.cpp'}
SINIT_END = {F[fa[x]]['addr'] + F[fa[x]]['size'] for x in SINIT if x in fa}
def ok_move(a, b, old, new):
    lo, hi = min(old, new), max(old, new)
    if text[a][2] in FROZEN or text[b][2] in FROZEN: return False
    if text[a][1] in SINIT_END: return False                            # a unit ending in its __sinit is exact
    if hi - lo > 0x800: return False
    if any(lo <= x < hi for x in SINIT): return False                 # __sinit ends are exact
    if not (text[a][0] < new < text[b][1]): return False              # never empty a unit
    return True
moves = {}
for s in S:
    if s['sec'] != '.data' or s['size'] < 12: continue
    w = read(d, ds, s['addr'], s['size']); W = [struct.unpack('>I', w[i:i + 4])[0] for i in range(0, len(w) - 3, 4)]
    if len(W) < 3 or W[1] != 0 or not all(x in fa or x == 0 for x in W[2:]): continue
    slots = sorted({x for x in W[2:] if x in fa})
    if len(slots) < 2: continue
    owner = dunit(s['addr'])
    oi = next((i for i, t in enumerate(text) if t[2] == owner), None)
    if oi is None: continue
    for nb, side in ((oi + 1, 'next'), (oi - 1, 'prev')):
        if not (0 <= nb < len(text)) or text[nb][0] != (text[oi][1] if side == 'next' else text[nb][0]) and side == 'next' and text[nb][0] != text[oi][1]: continue
        mine = [x for x in slots if ti(x) == nb]
        if len(mine) < 2: continue
        if side == 'next':
            if text[nb][0] != text[oi][1]: continue
            j0, j1 = fa[text[nb][0]] if text[nb][0] in fa else None, fa[max(mine)]
            if j0 is None: continue
            seg = F[j0:j1 + 1]
            if all(f['addr'] in slots or GENERIC.match(f['name']) for f in seg):
                x = F[j1]['addr'] + F[j1]['size']
                if ok_move(oi, nb, text[oi][1], x): moves[(oi, nb)] = x
        else:
            if text[oi][0] != text[nb][1]: continue
            j0 = fa[min(mine)]; j1 = fa[text[oi][0]] - 1 if text[oi][0] in fa else None
            if j1 is None: continue
            seg = F[j0:j1 + 1]
            if all(f['addr'] in slots or GENERIC.match(f['name']) for f in seg):
                if ok_move(nb, oi, text[oi][0], F[j0]['addr']): moves[(nb, oi)] = F[j0]['addr']
print(f'{len(moves)} boundary moves')
for (a, b), x in list(moves.items())[:8]: print(f'  {text[a][2]} | {text[b][2]}: 0x{text[a][1]:08X} -> 0x{x:08X}')
if '--apply' in sys.argv:
    txt = open(P).read()
    for (a, b), x in moves.items():
        ua, ub = text[a][2], text[b][2]
        txt = re.sub(rf'(?m)^({re.escape(ua)}:\n(?:\t.*\n)*?\t\.text\s+start:0x\w+ end:0x){text[a][1]:08X}', lambda m: m.group(1) + f'{x:08X}', txt, count=1)
        txt = re.sub(rf'(?m)^({re.escape(ub)}:\n(?:\t.*\n)*?\t\.text\s+start:0x){text[b][0]:08X}', lambda m: m.group(1) + f'{x:08X}', txt, count=1)
    open(P, 'w').write(txt)
