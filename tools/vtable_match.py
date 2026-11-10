#!/usr/bin/env python3
"""Find ogws vtables in Resort and spread names through their slots.

For each ogws __vt__ symbol, map its slot functions to Resort by name and vote for the Resort
.data address where those functions sit at the same slot offsets. A vtable is accepted with >= 2
agreeing slots covering >= 50% of the mappable ones and a unique best address. Then:
- the Resort label at that address (if generic) is renamed to the ogws vtable name;
- generic Resort slot functions take the ogws slot function's name when the size ratio >= 0.6 and
  opcode similarity >= 0.75.
Usage: vtable_match.py SRC_DOL SRC_SYMBOLS DST_DOL DST_SYMBOLS [--apply]
"""
import collections, re, struct, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import symbols, dol_sections, read, GENERIC
from fuzzy_match import tokens, opsim

def words(dol, secs, a, n):
    b = read(dol, secs, a, n) or b''
    return [struct.unpack('>I', b[i:i + 4])[0] for i in range(0, len(b) - 3, 4)]

def main(sdol, ssym, ddol, dsym, *flags):
    so, ss = dol_sections(sdol); do, ds = dol_sections(ddol)
    S, D = symbols(ssym), symbols(dsym)
    sf = {s['addr']: s for s in S if s['func']}; df = {s['addr']: s for s in D if s['func']}
    dname = {s['name']: s['addr'] for s in D if s['func'] and not GENERIC.match(s['name'])}
    dat = [(a, sz, o) for a, sz, o in ds if a >= 0x80653FA0]          # data-side DOL sections
    pos = collections.defaultdict(list)
    for a, sz, o in dat:
        for i in range(0, sz - 3, 4):
            w = struct.unpack('>I', do[o + i:o + i + 4])[0]
            if w in df: pos[w].append(a + i)
    found, slot_ren = {}, {}; agree = collections.Counter(); diffs = []; shifted = 0
    for v in [s for s in S if s['name'].startswith('__vt__') and s['size'] >= 8]:
        slots = words(so, ss, v['addr'], v['size'])
        votes = collections.Counter(); mappable = 0
        for k, p in enumerate(slots):
            f = sf.get(p)
            if not f or f['name'] not in dname: continue
            mappable += 1
            for q in pos[dname[f['name']]]: votes[q - 4 * k] += 1
        if not votes: continue
        (best, n), *rest = votes.most_common(2) + [(None, 0)]
        if n < 2 or n < 0.5 * mappable or (rest and rest[0][1] == n): continue
        found[best] = v
        dslots = words(do, ds, best, v['size'])
        lab_sz = next((d['size'] for d in D if d['addr'] == best and not d['func']), None)
        bad = 0
        for p, q in zip(slots, dslots):
            if p in sf and q in df and not GENERIC.match(df[q]['name']) and not GENERIC.match(sf[p]['name']):
                ok = df[q]['name'] == sf[p]['name']; agree[ok] += 1; bad += not ok
                if not ok and len(diffs) < 8: diffs.append((sf[p]['name'][:60], df[q]['name'][:60]))
        if bad or lab_sz != v['size']: shifted += 1; continue    # layout changed: don't trust slot names
        for p, q in zip(slots, dslots):
            if p in sf and q in df and GENERIC.match(df[q]['name']) and not GENERIC.match(sf[p]['name']):
                a, b = sf[p]['size'], df[q]['size']
                if min(a, b) / max(a, b) >= 0.6 and opsim(tokens(read(so, ss, p, a)), tokens(read(do, ds, q, b))) >= 0.75:
                    slot_ren.setdefault(q, sf[p]['name'])
    taken = {s['name'] for s in D}
    lab = {s['addr']: s['name'] for s in D if not s['func']}
    vt_ren = {a: v['name'] for a, v in found.items() if a in lab and GENERIC.match(lab[a]) and v['name'] not in taken}
    slot_ren = {a: n for a, n in slot_ren.items() if n not in taken and n not in vt_ren.values()}
    print(f'already-named slots: {agree[True]} agree, {agree[False]} differ'); print(f'vtables with changed layout (slots not used): {shifted}')
    print(f'vtables located {len(found)}, labels renamed {len(vt_ren)} (no label at {sum(1 for a in found if a not in lab)}), slot fns renamed {len(slot_ren)}')
    if '--apply' in flags:
        L = open(dsym).read().split('\n')
        for i, l in enumerate(L):
            m = re.match(r'^(\S+) = (\.\w+):0x([0-9A-Fa-f]+);', l)
            if not m: continue
            a = int(m.group(3), 16); new = vt_ren.get(a) if m.group(2) != '.text' else slot_ren.get(a)
            if new and GENERIC.match(m.group(1)): L[i] = new + l[len(m.group(1)):]
        open(dsym, 'w').write('\n'.join(L))

if __name__ == '__main__': main(*sys.argv[1:])
