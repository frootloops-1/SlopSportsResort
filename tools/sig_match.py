#!/usr/bin/env python3
"""Match functions between two dtk projects by relocation-masked byte signatures.

Usage: sig_match.py SRC_DOL SRC_SYMBOLS DST_DOL DST_SYMBOLS OUT_JSON
Only names that are unique on both sides (same size + same masked bytes) are reported.
"""
import hashlib, json, re, struct, sys, collections

SYM = re.compile(r'^(\S+) = (\.[\w$.]+|\w+):0x([0-9A-Fa-f]+); // (.*)$')

def dol_sections(path):
    b = open(path, 'rb').read()
    offs = struct.unpack('>18I', b[0:72]); addrs = struct.unpack('>18I', b[72:144]); sizes = struct.unpack('>18I', b[144:216])
    return b, [(addrs[i], sizes[i], offs[i]) for i in range(18) if sizes[i]]

def read(dol, secs, addr, size):
    for a, s, o in secs:
        if a <= addr and addr + size <= a + s:
            return dol[o + addr - a:o + addr - a + size]
    return None

def symbols(path):
    out = []
    for line in open(path):
        m = SYM.match(line.rstrip('\n'))
        if not m: continue
        name, sec, addr, attrs = m.group(1), m.group(2), int(m.group(3), 16), m.group(4)
        sz = re.search(r'size:0x([0-9A-Fa-f]+)', attrs)
        out.append(dict(name=name, sec=sec, addr=addr, size=int(sz.group(1), 16) if sz else 0,
                        func='type:function' in attrs, attrs=attrs))
    return out

DFORM = set([7, 8, 10, 11, 12, 13, 14, 15, 24, 25, 26, 27, 28, 29]) | set(range(32, 56))
def masked(code):
    out = bytearray()
    for i in range(0, len(code) - 3, 4):
        w = struct.unpack('>I', code[i:i+4])[0]; op = w >> 26
        if op == 18: w &= 0xFC000003            # b/bl target
        elif op == 16: w &= 0xFFFF0003          # bc target
        elif op in DFORM: w &= 0xFFFF0000       # immediates / sda offsets / lo16 relocs
        out += struct.pack('>I', w)
    return bytes(out)

def sigs(dol, secs, syms):
    d = collections.defaultdict(list)
    for s in syms:
        if not s['func'] or s['size'] < 8: continue
        code = read(dol, secs, s['addr'], s['size'])
        if code is None: continue
        d[(s['size'], hashlib.sha1(masked(code)).hexdigest())].append(s)
    return d

GENERIC = re.compile(r"^(fn|lbl|func|dtor|ctor|sinit|gap|jumptable|switch|float|double|string|wstring)_[0-9A-Fa-f_]+(_data|_text|_rodata|_bss)?$")
def main(sd, ss, dd, ds, out):
    sdol, ssec = dol_sections(sd); ddol, dsec = dol_sections(dd)
    a = sigs(sdol, ssec, symbols(ss)); b = sigs(ddol, dsec, symbols(ds))
    res = []
    for k, src in a.items():
        if len(src) != 1 or k not in b or len(b[k]) != 1: continue
        s, d = src[0], b[k][0]
        if GENERIC.match(s['name']): continue
        res.append(dict(src=s['name'], src_addr=hex(s['addr']), dst=d['name'], dst_addr=hex(d['addr']), size=hex(s['size'])))
    json.dump(sorted(res, key=lambda r: int(r['dst_addr'], 16)), open(out, 'w'), indent=0)
    print(f'{len(res)} unique named matches -> {out}')

if __name__ == '__main__': main(*sys.argv[1:])
