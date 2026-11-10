#!/usr/bin/env python3
"""Port .text splits from other dtk projects by function name (no reference binary needed).

For each reference unit: look up its named functions in our symbols.txt. Accept the unit when
>= 2 names (and >= 60%) are found, they keep the reference order, and every named function
between the first and last hit belongs to that unit (unnamed fn_ functions are allowed inside).
Candidates are taken best-coverage first and never overlap existing or earlier splits.
Usage: port_splits.py DST_SYMBOLS DST_SPLITS DST_DOL REF_SYMBOLS:REF_SPLITS ... [--apply]
"""
import sys, os
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import symbols, dol_sections, read, GENERIC
from apply_ogws import parse_splits
from unit_paths import canonical

def candidates(fns, idx, byname, dol, secs, refs):
    """(coverage, hits, unit, start, end, ref name) for every reference .text unit found here."""
    cands = []
    for ref in refs:
        rsym, rspl = ref.split(':')
        rf = sorted([s for s in symbols(rsym) if s['func']], key=lambda s: s['addr'])
        for unit, ss in parse_splits(rspl).items():
            unit = canonical(unit)
            t = [x for x in ss if x[0] == '.text']
            if len(t) != 1: continue
            _, s, e = t[0]
            named = [f['name'] for f in rf if s <= f['addr'] < e and not GENERIC.match(f['name'])]
            hits = [byname[n] for n in named if n in byname]
            if len(hits) < 2 or len(hits) < 0.6 * len(named): continue
            addrs = [h['addr'] for h in hits]
            if addrs != sorted(addrs): continue
            i0, i1 = idx[addrs[0]], idx[addrs[-1]]
            nset = set(named)
            if any(not GENERIC.match(f['name']) and f['name'] not in nset for f in fns[i0:i1 + 1]): continue
            start, end = fns[i0]['addr'], fns[i1]['addr'] + fns[i1]['size']
            nxt = fns[i1 + 1]['addr'] if i1 + 1 < len(fns) else end
            pad = read(dol, secs, end, nxt - end) if nxt > end else b''
            if pad is not None and 0 < nxt - end < 0x20 and pad.strip(b'\0') == b'': end = nxt
            cands.append((len(hits) / len(named), len(hits), unit, start, end, os.path.basename(rspl)))
    return cands

def main(argv):
    apply = '--apply' in argv; argv = [a for a in argv if a != '--apply']
    dsym, dsplit, ddol, refs = argv[0], argv[1], argv[2], argv[3:]
    fns = sorted([s for s in symbols(dsym) if s['func']], key=lambda s: s['addr'])
    idx = {s['addr']: i for i, s in enumerate(fns)}; byname = {s['name']: s for s in fns}
    dol, secs = dol_sections(ddol)
    existing = parse_splits(dsplit)
    used = [(s, e) for u in existing.values() for (sec, s, e) in u if sec == '.text']
    names_taken = {u.lower() for u in existing}
    cands = candidates(fns, idx, byname, dol, secs, refs)
    new = []
    for cov, n, unit, start, end, src in sorted(cands, key=lambda c: (-c[0], -c[1])):
        if unit.lower() in names_taken or any(not (end <= us or start >= ue) for us, ue in used): continue
        names_taken.add(unit.lower()); used.append((start, end)); new.append((start, end, unit, src))
    by = {}
    for *_, src in new: by[src] = by.get(src, 0) + 1
    print(f'{len(cands)} candidates, {len(new)} new .text splits {by}')
    if apply:
        with open(dsplit, 'a') as f:
            for start, end, unit, _ in sorted(new):
                f.write(f'\n{unit}:\n\t.text       start:0x{start:08X} end:0x{end:08X}\n')

if __name__ == '__main__': main(sys.argv[1:])
