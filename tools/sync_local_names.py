#!/usr/bin/env python3
"""Re-sync compiler-numbered local data names (@N) in symbols.txt with the built objects.

MWCC numbers anonymous locals (@21048 ...) per translation unit, and the numbers shift whenever a header
in the precompiled prefix changes. objdiff pairs data by name, so a matched unit drops to 99.9% when
symbols.txt still carries the old @N. For every Matching unit (configure.py Object(Matching, ...) and
ported_objects.json) this pairs the object's local @N data symbols with the @N entries of symbols.txt inside the unit's
split range, in address order per section (linker dead-stripping shifts offsets, so only the order
is kept), and renames those that differ when both sides have the same count. Run after `ninja`. Usage: sync_local_names.py [--apply]"""
import json, re, subprocess, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from apply_ogws import parse_splits

CFG = 'config/RZTE01_01'
units = re.findall(r'Object\(Matching, "([^"]+)"', open('configure.py').read())
units += [o['name'] for o in json.load(open(f'{CFG}/ported_objects.json'))]
sp = parse_splits(f'{CFG}/splits.txt')
text = open(f'{CFG}/symbols.txt').read()
ren = []
for u in units:
    obj = f'build/RZTE01_01/src/' + re.sub(r'\.(c|cpp)$', '.o', u)
    if u not in sp or not os.path.exists(obj): continue
    rng = {sec: (s, e) for sec, s, e in sp[u]}
    out = subprocess.run(['build/binutils/powerpc-eabi-objdump', '-t', obj], capture_output=True, text=True).stdout
    objn = {}
    for m in re.finditer(r'^([0-9a-f]{8}) l\s+O (\S+)\s+[0-9a-f]+ (@\d+)$', out, re.M):
        objn.setdefault(m[2], []).append((int(m[1], 16), m[3]))
    for sec, lst in objn.items():
        if sec not in rng: continue
        s0, e0 = rng[sec]
        # unreferenced locals are dead-stripped at link, so offsets do not carry over: pair the @N
        # names in address order, and only when both sides have the same count
        dol = [(int(m[2], 16), m[1]) for m in re.finditer(rf'(?m)^(@\d+) = {re.escape(sec)}:0x([0-9A-F]+);', text)
               if s0 <= int(m[2], 16) < e0]
        if len(dol) != len(lst): continue
        for (_, old), (_, name) in zip(sorted(dol), sorted(lst)):
            if old != name:
                ren.append((old, name, u))
                text = re.sub(rf'(?m)^{re.escape(old)} = ', name + ' = ', text, count=1)
for old, new, u in ren: print(f'{u}: {old} -> {new}')
print(f'{len(ren)} renames')
if '--apply' in sys.argv: open(f'{CFG}/symbols.txt', 'w').write(text)
