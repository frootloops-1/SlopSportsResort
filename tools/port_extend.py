#!/usr/bin/env python3
"""Extend a ported unit's .text over functions Resort has under placeholder names.

Walks the compiled object's .text functions in address order against Resort's function symbols from
the split's .text start. Where Resort has a generic name (fn_/gap_) at the expected address with the same size
(or the same address for the last, padded function), rename it to the object's name. Prints the new .text end;
--apply rewrites symbols.txt and splits.txt. Check the result with obj_score and the DOL gate.
Usage: port_extend.py UNIT OBJ [--apply]"""
import re, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from obj_score import elf
from sig_match import symbols
from apply_ogws import parse_splits

def main(unit, obj, *flags):
    cfg = 'config/RZTE01_01'
    b, secs, syms, _ = elf(obj)
    ti = next(i for i, s in enumerate(secs) if s['name'] == '.text')
    of = sorted([s for s in syms if s['type'] == 2 and s['shndx'] == ti], key=lambda s: s['value'])
    rs = {s['addr']: s for s in symbols(f'{cfg}/symbols.txt') if s['func']}
    ts = next(s for n, s, e in parse_splits(f'{cfg}/splits.txt')[unit] if n == '.text')
    ren = {}; end = ts
    for f in of:
        a = ts + f['value']; r = rs.get(a)
        if r is None: print(f'stop: no Resort function at {a:#x} for {f["name"]}'); break
        if r['name'] != f['name']:
            if not re.match(r'(fn|gap)_', r['name']): print(f'stop: {a:#x} is {r["name"]}, object has {f["name"]}'); break
            if r['size'] != f['size']: print(f'note: size {r["size"]:#x} vs {f["size"]:#x} at {a:#x} ({f["name"]})')
            ren[r['name']] = f['name']
        end = a + r['size']
    for k, v in ren.items(): print(f'rename {k} -> {v}')
    print(f'.text end {end:#x}')
    if '--apply' in flags:
        p = f'{cfg}/symbols.txt'; t = open(p).read()
        for k, v in ren.items(): t = re.sub(rf'(?m)^{re.escape(k)} = ', f'{v} = ', t)
        open(p, 'w').write(t)
        p = f'{cfg}/splits.txt'; t = open(p).read()
        blk = re.search(rf'(?m)^{re.escape(unit)}:\n(\t.*\n)+', t).group(0)
        nb = re.sub(r'(\t\.text\s+start:0x\w+ end:0x)\w+', lambda m: m.group(1) + f'{end:08X}', blk)
        open(p, 'w').write(t.replace(blk, nb))

if __name__ == '__main__': main(*sys.argv[1:])
