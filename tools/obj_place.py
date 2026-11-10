#!/usr/bin/env python3
"""Check whether an object's whole .text matches the DOL contiguously at ADDR (relocated fields
masked), function by function. Usage: obj_place.py OBJ DOL ADDR"""
import struct, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from obj_score import elf
from sig_match import dol_sections, read
b, secs, syms, relocs = elf(sys.argv[1]); d, ds = dol_sections(sys.argv[2]); base = int(sys.argv[3], 16)
ti = next(i for i, s in enumerate(secs) if s['name'] == '.text')
text = bytearray(b[secs[ti]['off']:secs[ti]['off'] + secs[ti]['size']])
dol = bytearray(read(d, ds, base, len(text)))
for off, typ in relocs.get(ti, []):
    o4 = off & ~3; m = 0xFFFF if typ in (4, 5, 6) else {10: 0x03FFFFFC, 109: 0x1FFFFF, 11: 0xFFFC}.get(typ, 0xFFFFFFFF)
    for buf in (text, dol):
        w = struct.unpack('>I', buf[o4:o4 + 4])[0] & ~m & 0xFFFFFFFF; buf[o4:o4 + 4] = struct.pack('>I', w)
ok = 0; fns = sorted((s['value'], s['size'], s['name']) for s in syms if s['type'] == 2 and s['shndx'] == ti)
for v, sz, n in fns:
    same = text[v:v + sz] == dol[v:v + sz]; ok += same
    print(f"{'OK ' if same else 'BAD'} 0x{base + v:08X} {sz:#6x} {n[:70]}")
print(f'{ok}/{len(fns)} functions match at 0x{base:08X}; object .text ends at 0x{base + len(text):08X}')
