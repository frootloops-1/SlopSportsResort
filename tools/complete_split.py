#!/usr/bin/env python3
"""Find where a compiled object's data sections live in the target DOL, from its .text relocations.

Each relocation in .text that targets a data section (via a section or object symbol + addend) is
decoded in the target DOL's instructions at the same offset (lis/addi pairs, r13/r2 SDA21), giving
target_addr - offset_in_section = section start. Prints split lines when all relocations of a
section agree. Usage: complete_split.py OBJ DOL SYMBOLS TEXT_START"""
import collections, struct, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import dol_sections, read, symbols
from fuzzy_match import sda_bases

def elf_full(path):
    b = open(path, 'rb').read()
    shoff, = struct.unpack('>I', b[32:36]); shentsize, shnum, shstrndx = struct.unpack('>HHH', b[46:52])
    sh = [struct.unpack('>IIIIIIIIII', b[shoff + i * shentsize: shoff + i * shentsize + 40]) for i in range(shnum)]
    def nm(off, tab): e = b.index(b'\0', tab + off); return b[tab + off:e].decode('latin1')
    secs = [dict(name=nm(s[0], sh[shstrndx][4]), type=s[1], off=s[4], size=s[5], link=s[6], info=s[7], align=s[8]) for s in sh]
    st = next(s for s in secs if s['type'] == 2); strt = secs[st['link']]['off']
    syms = []
    for i in range(st['size'] // 16):
        n, val, sz, inf, oth, shn = struct.unpack('>IIIBBH', b[st['off'] + i * 16: st['off'] + i * 16 + 16])
        syms.append(dict(name=nm(n, strt), value=val, size=sz, type=inf & 15, shndx=shn))
    rel = collections.defaultdict(list)
    for s in secs:
        if s['type'] == 4:
            for i in range(s['size'] // 12):
                off, inf, add = struct.unpack('>IIi', b[s['off'] + i * 12: s['off'] + i * 12 + 12])
                rel[s['info']].append((off, inf & 0xFF, inf >> 8, add))
    return secs, syms, rel

def main(obj, dolp, symp, tstart):
    tstart = int(tstart, 16)
    dol, ds = dol_sections(dolp)
    ir = next(s['addr'] for s in symbols(symp) if s['name'] == '__init_registers')
    r13, r2 = sda_bases(dol, ds, ir)
    secs, syms, rel = elf_full(obj)
    ti = next(i for i, s in enumerate(secs) if s['name'] == '.text')
    W = lambda a: struct.unpack('>I', read(dol, ds, a, 4))[0]
    tgt = {x['name']: x['addr'] for x in symbols(symp) if x['func']}
    fns = sorted((x['value'], x['size'], x['name']) for x in syms if x['type'] == 2 and x['shndx'] == ti)
    def dol_addr(off):   # object .text offset -> DOL address via the containing function's name
        for v, sz, n in fns:
            if v <= off < v + sz and n in tgt: return tgt[n] + off - v
        return None
    est = collections.defaultdict(collections.Counter); pending_ha = {}
    for off, typ, si, add in sorted(rel[ti]):
        sym = syms[si]; tsec = sym['shndx']
        if tsec == 0 or tsec >= len(secs) or secs[tsec]['name'] == '.text': continue
        within = sym['value'] + add
        da = dol_addr(off & ~3)
        if da is None: continue
        ins = W(da)
        if typ == 6:   # ADDR16_HA
            pending_ha[(ins >> 21) & 31] = ((ins & 0xFFFF) << 16, tsec, within)
        elif typ == 4:  # ADDR16_LO: base register is ra
            ra = (ins >> 16) & 31; lo = ins & 0xFFFF; lo -= 0x10000 if lo & 0x8000 else 0
            if ra in pending_ha:
                hi, s2, w2 = pending_ha[ra]; addr = (hi + lo) & 0xFFFFFFFF
                if hi & 0x8000 == 0 or True: est[tsec][addr - within] += 1
        elif typ == 109:  # EMB_SDA21
            ra = (ins >> 16) & 31; lo = ins & 0xFFFF; lo -= 0x10000 if lo & 0x8000 else 0
            base = r13 if ra == 13 else r2 if ra == 2 else 0
            est[tsec][(base + lo - within) & 0xFFFFFFFF] += 1
    for tsec, c in est.items():
        (start, n), *rest = c.most_common()
        s = secs[tsec]; flag = '' if not rest else f'   (disagreeing: {rest[:3]})'
        print(f"\t{s['name']:<11} start:0x{start:08X} end:0x{start + s['size']:08X}   # {n} refs{flag}")

if __name__ == '__main__': main(*sys.argv[1:])
