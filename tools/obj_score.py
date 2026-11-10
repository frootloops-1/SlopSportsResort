#!/usr/bin/env python3
"""Score a compiled .o against the target DOL: for each function in the object's .text that has a
same-named function in SYMBOLS, compare bytes with relocated fields masked on both sides.
Usage: obj_score.py OBJ DOL SYMBOLS  -> prints 'exact/total' and per-function status with -v"""
import struct, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import symbols, dol_sections, read

def elf(path):
    b = open(path, 'rb').read()
    shoff, = struct.unpack('>I', b[32:36]); shentsize, shnum, shstrndx = struct.unpack('>HHH', b[46:52])
    sh = [struct.unpack('>IIIIIIIIII', b[shoff + i * shentsize: shoff + i * shentsize + 40]) for i in range(shnum)]
    def name(off, tab): e = b.index(b'\0', tab + off); return b[tab + off:e].decode('latin1')
    shs = sh[shstrndx][4]
    secs = [dict(name=name(s[0], shs), type=s[1], off=s[4], size=s[5], link=s[6], info=s[7]) for s in sh]
    syms = []; symtab = next(i for i, s in enumerate(secs) if s['type'] == 2)
    st = secs[symtab]; strt = secs[st['link']]['off']
    for i in range(st['size'] // 16):
        nm, val, sz, inf, oth, shn = struct.unpack('>IIIBBH', b[st['off'] + i * 16: st['off'] + i * 16 + 16])
        syms.append(dict(name=name(nm, strt), value=val, size=sz, type=inf & 15, shndx=shn))
    relocs = {}
    for s in secs:
        if s['type'] == 4:
            tgt = s['info']; L = relocs.setdefault(tgt, [])
            for i in range(s['size'] // 12):
                off, inf, add = struct.unpack('>IIi', b[s['off'] + i * 12: s['off'] + i * 12 + 12]); L.append((off, inf & 0xFF))
    return b, secs, syms, relocs

MASK = {10: 0x03FFFFFC, 4: 0xFFFF, 5: 0xFFFF, 6: 0xFFFF, 109: 0x1FFFFF, 11: 0xFFFC, 1: 0xFFFFFFFF}
def score(obj, dol, symp, verbose=False):
    b, secs, syms, relocs = elf(obj)
    ti = next(i for i, s in enumerate(secs) if s['name'] == '.text')
    text = bytearray(b[secs[ti]['off']:secs[ti]['off'] + secs[ti]['size']])
    roffs = {off: t for off, t in relocs.get(ti, [])}
    d, ds = dol_sections(dol); target = {s['name']: s for s in symbols(symp) if s['func']}
    ok = tot = 0; rows = []
    for s in syms:
        if s['type'] != 2 or s['shndx'] != ti or s['name'] not in target: continue
        t = target[s['name']]; tot += 1
        if t['size'] != s['size']: rows.append((s['name'], f'size {s["size"]:#x} vs {t["size"]:#x}')); continue
        mine = bytearray(text[s['value']:s['value'] + s['size']]); theirs = bytearray(read(d, ds, t['addr'], t['size']))
        for off, typ in roffs.items():
            if s['value'] <= off < s['value'] + s['size']:
                o = off - s['value']; m = MASK.get(typ, 0xFFFFFFFF)
                if typ in (4, 5, 6): o -= 2; m = 0xFFFF0000 | 0  # half-word relocs point at the low half
                o4 = (off - s['value']) & ~3
                for buf in (mine, theirs):
                    w = struct.unpack('>I', buf[o4:o4 + 4])[0]
                    w &= ~(0xFFFF if typ in (4, 5, 6) else MASK.get(typ, 0xFFFFFFFF)) & 0xFFFFFFFF
                    buf[o4:o4 + 4] = struct.pack('>I', w)
        same = mine == theirs; ok += same
        if not same:
            n = sum(1 for i in range(0, len(mine), 4) if mine[i:i + 4] != theirs[i:i + 4]); rows.append((s['name'], f'{n} words differ'))
    print(f'{ok}/{tot} exact')
    if verbose:
        for r in rows[:15]: print('  ', *r)
    return ok, tot

if __name__ == '__main__': score(sys.argv[1], sys.argv[2], sys.argv[3], '-v' in sys.argv)
