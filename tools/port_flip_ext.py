#!/usr/bin/env python3
"""Turn fully exact scan results into Matching objects.

For each (unit, compiler) in PORT_FULL_JSON: take the scan's object, locate every allocated data
section in Resort via complete_split, extend the .text range to every object function present by
name, copy the ogws source file, and record {name, mw_version, cflags} in
config/RZTE01_01/ported_objects.json (read by configure.py). Units with an unlocatable or
overlapping section are skipped. Usage: port_flip.py OGWS RESORT SCAN_JSON PORT_FULL_JSON"""
import io, contextlib, json, os, re, shutil, subprocess, sys
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import symbols
from apply_ogws import parse_splits
import complete_split as cs
import struct
from sig_match import dol_sections, read as dolread
_D,_DS=dol_sections('orig/RZTE01_01/sys/main.dol')
def extab_find(lo,hi,secs):
    W=lambda a: struct.unpack('>I',dolread(_D,_DS,a,4))[0]
    ents=[]
    a=0x80006B40
    while a<0x800071C0:
        f=W(a)
        if lo<=f<hi: ents.append((a,f,W(a+4),W(a+8)))
        a+=12
    if not ents: return {}
    xi=(ents[0][0],ents[-1][0]+12)
    sz={x['name']:x['size'] for x in secs}
    assert xi[1]-xi[0]==sz.get('extabindex',0),(xi,sz.get('extabindex'))
    xs=min(e[3] for e in ents)
    return {'extab':(xs,xs+sz['extab']),'extabindex':xi}


SKIP = {'.text', '.comment', '.symtab', '.strtab', '.shstrtab', ''}
def main(og, rs, scanj, fullj):
    scan = {r['unit']: r for r in json.load(open(scanj))}
    full = json.load(open(fullj))
    cfg = f'{rs}/config/RZTE01_01'
    sp = parse_splits(f'{cfg}/splits.txt')
    used = [(s, e, u) for u, v in sp.items() for (sec, s, e) in v]
    allsyms = symbols(f'{cfg}/symbols.txt')
    fa = {s['name']: s for s in allsyms if s['func']}
    pj = f'{cfg}/ported_objects.json'
    ported = json.load(open(pj)) if os.path.exists(pj) else []
    done = {p['name'] for p in ported}
    text = open(f'{cfg}/splits.txt').read()
    added = skipped = 0
    for unit, ver in full:
        if unit in done or unit.startswith('Pack/'): continue
        obj = scan[unit]['results'][ver]['obj']
        secs, syms, rel = cs.elf_full(obj)
        buf = io.StringIO()
        with contextlib.redirect_stdout(buf): cs.main(obj, f'{rs}/orig/RZTE01_01/sys/main.dol', f'{cfg}/symbols.txt', '0')
        found = {}
        for line in buf.getvalue().splitlines():
            m = re.match(r'\t(\S+)\s+start:0x(\w+) end:0x(\w+)\s+# \d+ refs(.*)', line)
            if m and not m.group(4): found[m.group(1)] = (int(m.group(2), 16), int(m.group(3), 16))
        if 'extab' not in found:
            _t=[x for x in secs if x['name']=='extab']
            if _t:
                tix=next(i for i,s_ in enumerate(secs) if s_['name']=='.text')
                nm_=[x['name'] for x in syms if x['type']==2 and x['shndx']==tix and x['name'] in fa]
                try: found.update(extab_find(min(fa[n]['addr'] for n in nm_),max(fa[n]['addr']+fa[n]['size'] for n in nm_),secs))
                except AssertionError as e: print('extab mismatch',unit,e)
        alloc = [s['name'] for s in secs if s['type'] in (1, 8) and s['size'] and s['name'] not in SKIP]
        for a_ in [a for a in alloc if a not in found]:
            si_ = next(i for i, s_ in enumerate(secs) if s_['name'] == a_)
            if secs[si_]['type'] == 1:
                ob = open(obj, 'rb').read()[secs[si_]['off']:secs[si_]['off'] + secs[si_]['size']]
                mk = bytearray(len(ob)); 
                for (ro, rt, rs_, ra_) in rel.get(si_, []):
                    mk[ro:ro + (4 if rt in (1, 18, 19, 20) else 2)] = b'\xff' * (4 if rt in (1, 18, 19, 20) else 2)
                pat = b''.join(re.escape(bytes([ob[i]])) if not mk[i] else b'.' for i in range(len(ob)))
                hits = []
                for (da, dsz, doff) in _DS:
                    if da < 0x80006000: continue
                    blob = _D[doff:doff + dsz]
                    for m_ in re.finditer(b'(?s)' + pat, blob):
                        if (da + m_.start()) % 4 == 0: hits.append(da + m_.start())
                if len(hits) == 1 and sum(1 for i in range(len(ob)) if not mk[i] and ob[i]) >= 8:
                    print('  bytematch', unit, a_, hex(hits[0])); found[a_] = (hits[0], hits[0] + len(ob))
                else: print('  nomatch', unit, a_, len(hits))
        for a_ in [a for a in alloc if a not in found]:
            S_ = next(s_['size'] for s_ in secs if s_['name'] == a_)
            tsu = next(x for x in sp[unit] if x[0] == '.text')[1]
            prev = [(max(e for (n2,s2,e) in v if n2==a_), u2) for u2, v in sp.items() if u2 != unit and any(n2==a_ for n2,_,_ in v) and any(n2=='.text' and s2 < tsu for n2,s2,_ in v)]
            nxt = [(min(s2 for (n2,s2,e) in v if n2==a_), u2) for u2, v in sp.items() if u2 != unit and any(n2==a_ for n2,_,_ in v) and any(n2=='.text' and s2 > tsu for n2,s2,_ in v)]
            if not prev or not nxt: continue
            p_ = max(prev)[0]; q_ = min(nxt)[0]
            al = 8 if a_ in ('.data','.rodata','.sdata','.sbss','.sdata2','.sbss2') else 4
            al = 32 if a_=='.data' else al
            p2 = (p_ + al - 1) // al * al
            if 0 <= q_ - p_ and q_ - p2 < S_ + 32 and q_ - p_ >= S_:
                print('  guess', unit, a_, hex(p_), hex(q_), hex(S_))
                found[a_] = (p2, p2 + S_)
        # sections the unit's split already owns but relocations did not locate (.bss/.ctors of static-init units)
        for a_ in [a for a in alloc if a not in found]:
            cur = [x for x in sp[unit] if x[0] == a_]
            if cur: found[a_] = (cur[0][1], cur[0][2]); print('  keep split range', unit, a_)
        noexc = False
        if 'extab' not in found and 'extab' in alloc and unit.startswith('MSL/'):
            alloc = [a for a in alloc if a not in ('extab','extabindex')]; noexc = True
        if any(a not in found for a in alloc): skipped += 1; print('skip (section not located):', unit, [a for a in alloc if a not in found]); continue
        ti = next(i for i, s in enumerate(secs) if s['name'] == '.text')
        _t0 = next(x for x in sp[unit] if x[0] == '.text')[1]
        names = [x['name'] for x in syms if x['type'] == 2 and x['shndx'] == ti and x['name'] in fa and abs(fa[x['name']]['addr'] - _t0) < 0x1000]  # weak fns Resort places elsewhere
        lo = min(fa[n]['addr'] for n in names); hi = max(fa[n]['addr'] + fa[n]['size'] for n in names)
        (_, ts, te) = next(x for x in sp[unit] if x[0] == '.text')
        ts, te = min(ts, lo), max(te, hi)
        rng = {'.text': (ts, te), **found}
        # never shrink a range the splits already give this unit
        for n, s0, e0 in sp[unit]:
            if n in rng: rng[n] = (min(rng[n][0], s0), max(rng[n][1], e0))
        # a section end inside a Resort symbol is alignment padding: end at that symbol's end
        for n, (s, e) in list(rng.items()):
            for y in allsyms:
                if y['addr'] < e < y['addr'] + y['size'] and y['addr'] >= s: rng[n] = (s, y['addr'] + y['size'])
        if any(not (e <= s0 or s >= e0) for name, (s, e) in rng.items() for (s0, e0, u) in used if u != unit):
            skipped += 1; print('skip (overlap):', unit, {n:(hex(a),hex(b)) for n,(a,b) in rng.items()}, [(hex(s0),hex(e0),u) for name,(s,e) in rng.items() for (s0,e0,u) in used if u!=unit and not (e<=s0 or s>=e0)]); continue
        old = re.search(rf'(?m)^{re.escape(unit)}:\n(\t.*\n)+', text).group(0)
        new = f'{unit}:\n' + ''.join(f'\t{n:<11} start:0x{s:08X} end:0x{e:08X}\n' for n, (s, e) in rng.items())
        text = text.replace(old, new)
        used += [(s, e, unit) for s, e in rng.values()]
        cmd = subprocess.run(['ninja', '-t', 'commands', 'build/RSPE01_01/src/' + re.sub(r'\.(c|cpp|cp)$', '', unit) + '.o'], cwd=og, capture_output=True, text=True).stdout.strip().split('\n')[-1].split(' && ')[0]
        flags = re.search(r'mwcceppc\.exe (.*) -MMD', cmd).group(1)
        flags = re.sub(rf'-i build/RSPE01_01/include|-DBUILD_VERSION=\d+|-DVERSION_RSPE01_01', '', flags)
        # ogws headers branch on VERSION_RSPE01_01 (configure.py passes it to the base flags too)
        if noexc: flags = flags.replace('-Cpp_exceptions on', '-Cpp_exceptions off')
        flags += ' -i build/RZTE01_01/include -DBUILD_VERSION=0 -DVERSION_RZTE01_01 -DVERSION_RSPE01_01'
        os.makedirs(os.path.dirname(f'{rs}/src/{unit}'), exist_ok=True)
        shutil.copy(f'{og}/src/{unit}', f'{rs}/src/{unit}')
        ported.append(dict(name=unit, mw_version=ver, cflags=flags.split(), category='game' if unit.startswith('Pack/') else 'sdk'))
        added += 1
    open(f'{cfg}/splits.txt', 'w').write(text)
    json.dump(ported, open(pj, 'w'), indent=1)
    print(f'added {added}, skipped {skipped}')

if __name__ == '__main__': main(*sys.argv[1:])
