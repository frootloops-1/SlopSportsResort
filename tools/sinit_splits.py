#!/usr/bin/env python3
"""Add end-anchored splits from the .ctors table.

MWCC emits a unit's __sinit_* static initialiser as the last function of that unit, and .ctors
lists one pointer per unit in link order. For each __sinit not already inside a split, make a unit
that ends at the __sinit (plus trailing zero padding) and starts at the closest known boundary
before it (an existing split edge, a dtk auto-chunk start, or the previous __sinit end). The start
is an upper bound: several source files without static init may still be merged into one unit.
The unit also takes its 4-byte .ctors entry. Usage: sinit_splits.py CONFIG_DIR DOL OBJDIFF_JSON CTORS_START CTORS_SIZE [--apply]
"""
import json, re, struct, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import symbols, dol_sections, read
from apply_ogws import parse_splits

def main(cfg, dolp, odj, cstart, csize, *flags):
    cstart, csize = int(cstart, 16), int(csize, 16)
    dol, secs = dol_sections(dolp)
    fns = sorted([s for s in symbols(f'{cfg}/symbols.txt') if s['func']], key=lambda s: s['addr'])
    at = {f['addr']: i for i, f in enumerate(fns)}
    ct = read(dol, secs, cstart, csize)
    entries = [(cstart + i, struct.unpack('>I', ct[i:i + 4])[0]) for i in range(0, len(ct), 4)]
    entries = [(ea, p) for ea, p in entries if p in at]
    sp = parse_splits(f'{cfg}/splits.txt')
    text = sorted((s, e) for v in sp.values() for (sec, s, e) in v if sec == '.text')
    owned_ct = {s for v in sp.values() for (sec, s, e) in v if sec.startswith('.ctors')}
    bounds = {b for s, e in text for b in (s, e)}
    for u in json.load(open(odj))['units']:
        m = re.search(r'auto_\d+_([0-9A-F]{8})_text', u['name'])
        if m: bounds.add(int(m.group(1), 16))
    new = []
    for ea, p in entries:
        if ea in owned_ct or any(s <= p < e for s, e in text): continue
        f = fns[at[p]]; end = p + f['size']
        nxt = fns[at[p] + 1]['addr'] if at[p] + 1 < len(fns) else end
        pad = read(dol, secs, end, nxt - end) if nxt > end else b''
        if pad is not None and 0 < nxt - end < 0x20 and pad.strip(b'\0') == b'': end = nxt
        start = max(b for b in bounds if b <= p)
        if any(not (end <= s or start >= e) for s, e in text): continue
        text.append((start, end)); bounds.add(end); new.append((start, end, ea))
    print(f'{len(entries)} ctors entries, {len(new)} new sinit-anchored units')
    if '--apply' in flags:
        with open(f'{cfg}/splits.txt', 'a') as fh:
            for start, end, ea in sorted(new):
                fh.write(f'\nunk/sinit_{start:08X}.cpp:\n\t.text       start:0x{start:08X} end:0x{end:08X}\n'
                         f'\t.ctors      start:0x{ea:08X} end:0x{ea + 4:08X}\n')

if __name__ == '__main__': main(*sys.argv[1:])
