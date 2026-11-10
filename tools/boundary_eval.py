#!/usr/bin/env python3
"""Predict translation-unit starts in .text from inline-copy tails, and score against known splits.

A function is a 'copy' when its relocation-masked bytes occur at least K times in the DOL (header
inline functions are emitted again in every unit that uses them, and the linker keeps every copy).
Candidate boundary: a copy followed by a non-copy (a unit's tail of inline copies ends, the next
unit's own code begins). Optional: require the previous unit-tail run to have >= R copies.
Usage: boundary_eval.py DOL SYMBOLS [SPLITS] [--k K] [--run R] [--out JSON]"""
import argparse, collections, json, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import symbols, dol_sections, read, masked
from apply_ogws import parse_splits

def predict(dolp, symp, k, run, lo=None, hi=None):
    d, ds = dol_sections(dolp)
    F = sorted([f for f in symbols(symp) if f['func'] and f['size'] >= 4 and f['sec'] == '.text'], key=lambda f: f['addr'])
    key = [(f['size'], masked(read(d, ds, f['addr'], f['size']) or b'')) for f in F]
    cnt = collections.Counter(key)
    copy = [cnt[x] >= k and x[0] >= 0x10 for x in key]
    starts, r = [], 0
    for i in range(len(F) - 1):
        r = r + 1 if copy[i] else 0
        if copy[i] and not copy[i + 1] and r >= run:
            starts.append(F[i + 1]['addr'])
    return starts, F

def main():
    ap = argparse.ArgumentParser(); ap.add_argument('dol'); ap.add_argument('sym'); ap.add_argument('splits', nargs='?')
    ap.add_argument('--k', type=int, default=3); ap.add_argument('--run', type=int, default=1); ap.add_argument('--out')
    a = ap.parse_args()
    starts, F = predict(a.dol, a.sym, a.k, a.run)
    if a.splits:
        sp = parse_splits(a.splits)
        true = sorted({s for v in sp.values() for (sec, s, e) in v if sec == '.text'})
        lo, hi = true[0], max(e for v in sp.values() for (sec, s, e) in v if sec == '.text')
        fstarts = {f['addr'] for f in F}
        true = [t for t in true if t in fstarts]
        P = [s for s in starts if lo <= s < hi]
        tp = len(set(P) & set(true))
        print(f'k={a.k} run={a.run}: predicted {len(P)}, true {len(true)}, hits {tp}, precision {tp / max(len(P), 1):.1%}, recall {tp / len(true):.1%}')
    if a.out: json.dump(starts, open(a.out, 'w'))
    return starts

if __name__ == '__main__': main()
