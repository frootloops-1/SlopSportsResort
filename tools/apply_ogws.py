#!/usr/bin/env python3
"""Apply sig_match.py results: rename functions in symbols.txt and port .text splits for
ogws translation units whose functions all matched, in order and contiguously.

Usage: apply_ogws.py MATCHES_JSON OGWS_SYMBOLS OGWS_SPLITS DST_SYMBOLS DST_SPLITS DST_DOL
"""
import json, re, struct, sys, collections
sys.path.insert(0, __import__('os').path.dirname(__file__))
from sig_match import symbols, dol_sections, read, GENERIC

def confident(matches):
    by_src = sorted(matches, key=lambda r: int(r['src_addr'], 16))
    keep = []
    for i, r in enumerate(by_src):
        if int(r['size'], 16) >= 0x80: keep.append(r); continue
        ok = False
        for j in (i - 1, i + 1):
            if 0 <= j < len(by_src):
                n = by_src[j]
                ds = int(n['src_addr'], 16) - int(r['src_addr'], 16)
                dd = int(n['dst_addr'], 16) - int(r['dst_addr'], 16)
                if ds * dd > 0 and abs(dd - ds) < 0x400: ok = True
        if ok: keep.append(r)
    return keep

def parse_splits(path):
    units, cur = collections.OrderedDict(), None
    for line in open(path):
        if line.strip() == '' or line.startswith('Sections:'): cur = None; continue
        if not line.startswith('\t') and line.rstrip().endswith(':'):
            cur = line.rstrip()[:-1]; units[cur] = []; continue
        if cur and line.startswith('\t'):
            m = re.match(r'\t(\S+)\s+start:0x([0-9A-Fa-f]+) end:0x([0-9A-Fa-f]+)', line)
            if m: units[cur].append((m.group(1), int(m.group(2), 16), int(m.group(3), 16)))
    return units

def main(mj, osym, osplit, dsym, dsplit, ddol):
    matches = confident(json.load(open(mj)))
    src2dst = {int(r['src_addr'], 16): int(r['dst_addr'], 16) for r in matches}
    dst_name = {int(r['dst_addr'], 16): r['src'] for r in matches}
    osyms = [s for s in symbols(osym) if s['func']]
    dsyms = [s for s in symbols(dsym) if s['func']]
    dfun = sorted(dsyms, key=lambda s: s['addr']); didx = {s['addr']: i for i, s in enumerate(dfun)}
    dol, secs = dol_sections(ddol)

    # 1. rename
    taken = {s['name'] for s in symbols(dsym)}
    lines, renamed = open(dsym).read().split('\n'), 0
    for i, line in enumerate(lines):
        m = re.match(r'^(\S+) = \.text:0x([0-9A-Fa-f]+);', line)
        if not m: continue
        a = int(m.group(2), 16)
        if a in dst_name and GENERIC.match(m.group(1)) and dst_name[a] not in taken:
            taken.add(dst_name[a]); lines[i] = dst_name[a] + line[len(m.group(1)):]; renamed += 1
    open(dsym, 'w').write('\n'.join(lines))

    # 2. splits (.text only)
    existing = parse_splits(dsplit)
    used = [(s, e) for u in existing.values() for (sec, s, e) in u if sec == '.text']
    new = []
    for unit, secs_ in parse_splits(osplit).items():
        if unit in existing: continue
        t = [x for x in secs_ if x[0] == '.text']
        if len(t) != 1: continue
        _, s, e = t[0]
        fns = [f for f in osyms if s <= f['addr'] < e]
        if not fns or any(f['addr'] not in src2dst for f in fns): continue
        d = [src2dst[f['addr']] for f in fns]
        ix = [didx.get(a) for a in d]
        if None in ix or ix != list(range(ix[0], ix[0] + len(ix))): continue
        last = dfun[ix[-1]]; start, end = d[0], last['addr'] + last['size']
        nxt = dfun[ix[-1] + 1]['addr'] if ix[-1] + 1 < len(dfun) else end
        pad = read(dol, secs, end, nxt - end) if nxt > end else b''
        if pad is not None and nxt - end < 0x20 and pad.strip(b'\0') == b'': end = nxt
        if any(not (end <= us or start >= ue) for us, ue in used): continue
        used.append((start, end)); new.append((start, unit, end))
    with open(dsplit, 'a') as f:
        for start, unit, end in sorted(new):
            f.write(f'\n{unit}:\n\t.text       start:0x{start:08X} end:0x{end:08X}\n')
    print(f'confident matches {len(matches)}, renamed {renamed}, new text splits {len(new)}')

if __name__ == '__main__': main(*sys.argv[1:])
