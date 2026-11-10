#!/usr/bin/env python3
"""Merge a `pos=ADDR len=N sym=NAME` list (riptl/wii-symbols format) into symbols.txt.
Renames only generic dtk functions at the same address with the same size; reports agreement
against already-named functions first. Usage: merge_addr_list.py LIST SYMBOLS [--apply]"""
import re, sys, collections
sys.path.insert(0, __import__('os').path.dirname(__file__))
from sig_match import symbols, GENERIC

def main(lst, sym, *flags):
    P = [(int(a, 16), int(b), n) for a, b, n in re.findall(r'pos=(\w+) len=(\d+) sym=(\S+)', open(lst).read())]
    cnt = collections.Counter(n for *_, n in P)
    syms = symbols(sym); fns = {s['addr']: s for s in syms if s['func']}; taken = {s['name'] for s in syms}
    ok = bad = 0; ren = {}; why = collections.Counter(); badex = []
    for a, l, n in P:
        s = fns.get(a)
        if not s: why['no dtk fn'] += 1; continue
        if s['size'] != l: why['size differs'] += 1; continue
        if not GENERIC.match(s['name']):
            if s['name'] == n or s['name'].startswith(n + '__'): ok += 1
            else: bad += 1; badex.append((hex(a), n, s['name']))
            continue
        if cnt[n] > 1 or n in taken: why['dup/taken'] += 1; continue
        ren[a] = n; taken.add(n)
    print(f'agree {ok}, disagree {bad} {badex[:5]}; skipped {dict(why)}; {len(ren)} new names')
    if '--apply' in flags:
        lines = open(sym).read().split('\n')
        for i, line in enumerate(lines):
            m = re.match(r'^(\S+) = \.text:0x([0-9A-Fa-f]+);', line)
            if m and int(m.group(2), 16) in ren:
                lines[i] = ren[int(m.group(2), 16)] + line[len(m.group(1)):]
        open(sym, 'w').write('\n'.join(lines))

if __name__ == '__main__': main(*sys.argv[1:])
