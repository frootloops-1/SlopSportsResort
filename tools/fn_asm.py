#!/usr/bin/env python3
"""Print one function's dtk assembly compactly, annotating float/double constants and strings.
Usage: fn_asm.py NAME_OR_ADDR [ASM_DIR]"""
import re, struct, subprocess, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import symbols, dol_sections, read
from fuzzy_match import cstring
key = sys.argv[1]; asm = sys.argv[2] if len(sys.argv) > 2 else 'build/RZTE01_01/asm'
S = symbols('config/RZTE01_01/symbols.txt'); by = {s['name']: s for s in S}
f = by.get(key) or next(s for s in S if s['func'] and s['addr'] == int(key, 16))
d, ds = dol_sections('orig/RZTE01_01/sys/main.dol')
hit = subprocess.run(['grep', '-rlE', rf'^\.fn {re.escape(f["name"])},', asm], capture_output=True, text=True).stdout.split()
lines = open(hit[0]).read().split('\n')
i0 = next(i for i, l in enumerate(lines) if l.startswith(f'.fn {f["name"]},'))
print(f'{f["name"]} @ 0x{f["addr"]:08X} size {f["size"]:#x}')
for l in lines[i0 + 1:]:
    if l.startswith('.endfn'): break
    m = re.match(r'/\* ([0-9A-F]{8}) [0-9A-F]{8}  (?:[0-9A-F]{2} ){4}\*/\t(.*)', l)
    if not m:
        if l.strip(): print(l.strip())
        continue
    ins = m.group(2); note = ''
    for name in re.findall(r'(lbl_[0-9A-F]{8}|@\d+)', ins):
        s = by.get(name)
        if not s: continue
        if 'float' in s['attrs'] and s['size'] == 4: note = f'{struct.unpack(">f", read(d, ds, s["addr"], 4))[0]:g}'
        elif 'double' in s['attrs']: note = f'{struct.unpack(">d", read(d, ds, s["addr"], 8))[0]:g}'
        elif 'string' in s['attrs']: note = repr(cstring(d, ds, s['addr']))
    print(f'  {m.group(1)[-4:]}  {ins}' + (f'   ; {note}' if note else ''))
