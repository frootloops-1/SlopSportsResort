#!/usr/bin/env python3
"""After port_flip: compare each ported object's section sizes with its split ranges.
port_scan only checks that Resort's functions exist in the object; an object with extra or longer
code (newer/older library version) still scores exact but shifts the link. Run before the DOL gate;
.text differences that are not end padding mean the unit is not a real match.
Usage: port_sizecheck.py [PRE_FLIP_PORTED_JSON]   (only units added since that list)"""
import json, os, re, subprocess, sys
sys.path.insert(0, os.path.dirname(__file__))
from apply_ogws import parse_splits

sp = parse_splits('config/RZTE01_01/splits.txt')
pre = {o['name'] for o in json.load(open(sys.argv[1]))} if len(sys.argv) > 1 else set()
for u in [o['name'] for o in json.load(open('config/RZTE01_01/ported_objects.json'))]:
    if u in pre: continue
    o = 'build/RZTE01_01/src/' + re.sub(r'\.(c|cpp)$', '.o', u)
    if not os.path.exists(o): print('no object (run ninja first):', u); continue
    h = subprocess.run(['build/binutils/powerpc-eabi-objdump', '-h', o], capture_output=True, text=True).stdout
    secs = {m[1]: int(m[2], 16) for m in re.finditer(r'^\s*\d+\s+(\S+)\s+([0-9a-f]+)', h, re.M)}
    bad = [f'{sec} obj {secs[sec]:#x} split {e - s:#x}' for sec, s, e in sp[u] if sec in secs and secs[sec] != e - s]
    if bad: print(u, '; '.join(bad))
