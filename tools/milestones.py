#!/usr/bin/env python3
"""Project milestones: measure each one and print (or write) the status table in docs/milestones.md.

Reads build/RZTE01_01/report.json (run `ninja build/RZTE01_01/report.json` first), config splits/symbols,
and docs/marker-ledger.md. Milestone definitions live in MILESTONES below; docs/milestones.md explains them.
Usage: milestones.py [--write]      (--write replaces the table between the STATUS markers in the doc)"""
import json, re, sys, os, datetime
sys.path.insert(0, os.path.dirname(__file__))
from apply_ogws import parse_splits

CFG = 'config/RZTE01_01'
LIB = ('revolution/', 'nw4r/', 'egg/', 'MSL/', 'runtime/', 'MetroTRK/', 'RVLFaceLib/', 'homebuttonMiniLib/')
GAME_START = 0x801C0000      # library code ends before the game code (EGG ends ~0x801C9580; see docs/sport_map.md)
RP_NAME = re.compile(r'(RPSys|RPGrp|RPSnd|RPUtl|RPAud|IRPSys|IRPGrp|RPBow)')


# The 28 Pack units seeded from Wii Sports source (M1); later carves add more Pack units (counted separately).
M1_UNITS = {'Pack/' + u for u in ['RPGraphics/RPGrpDrawPathShadowTexture', 'RPGraphics/RPGrpViewRender2D', 'RPKernel/RPSysSystem', 'RPSystem/RPSysSceneMgr', 'RPSystem/RPSysGameConfig', 'RPSystem/RPSysTagParms', 'RPSystem/RPSysResourceManager', 'RPSystem/RPSysSaveDataMgr', 'RPKernel/RPSysTextWriter', 'RPKernel/RPSysEffectMgr', 'RPKernel/RPSysEffectBase', 'RPKernel/RPSysEffectCreator', 'RPKernel/RPSysHomeMenuMgr', 'RPKernel/RPSysKokeshiManager', 'RPGraphics/RPGrpCamera', 'RPGraphics/RPGrpDrawPathManager', 'RPGraphics/RPGrpModelAnmImplement', 'RPGraphics/RPGrpModelImplement', 'RPGraphics/RPGrpRenderer', 'RPGraphics/RPGrpView', 'RPGraphics/RPGrpViewRender3D', 'RPGraphics/RPGrpDrawPathLightMap', 'RPGraphics/RPGrpModelBoundingInfo', 'RPGraphics/RPGrpShadowTexture', 'RPGraphics/RPGrpCaptureTexture', 'RPSports/RPBowScene/RPBowBallReturnRack', 'RPSports/RPBowScene/RPBow_80323790', 'RPSports/RPBowScene/RPBowPinSetter']}


def measures():
    r = json.load(open('build/RZTE01_01/report.json'))
    m = {'total': [0, 0], 'library': [0, 0], 'rp': [0, 0], 'game': [0, 0]}
    units = {'rp_done': 0, 'rp_total': 0, 'lib_done': 0, 'm1_done': 0}
    lib_gap = 0
    for u in r['units']:
        n = u['name'].removeprefix('main/'); mm = u['measures']
        t, c = int(mm.get('total_code', 0)), int(mm.get('complete_code', 0))
        m['total'][0] += t; m['total'][1] += c
        a = re.match(r'auto_\d+_([0-9A-F]{8})_text', n)
        if n.startswith(LIB) or (a and int(a[1], 16) < GAME_START):
            k = 'library'
            if a: lib_gap += t
        elif n.startswith('Pack/'): k = 'rp'
        else: k = 'game'
        m[k][0] += t; m[k][1] += c
        if n.startswith('Pack/') and t:
            units['rp_total'] += 1; units['rp_done'] += c == t
            if n in M1_UNITS: units['m1_done'] += c == t
        if n.startswith(LIB) and t and c == t: units['lib_done'] += 1
    pct = {k: 100.0 * c / t if t else 0.0 for k, (t, c) in m.items()}
    # RP framework functions (by name) that sit inside Pack/ splits
    sp = parse_splits(f'{CFG}/splits.txt')
    pack = [(s, e) for u, v in sp.items() if u.startswith('Pack/') for sec, s, e in v if sec == '.text']
    rp_fns = in_pack = named = total_fns = 0
    for l in open(f'{CFG}/symbols.txt'):
        mm = re.match(r'(\S+) = \.text:0x(\w+); // type:function', l)
        if not mm: continue
        total_fns += 1; named += not mm[1].startswith(('fn_', 'gap_'))
        if RP_NAME.search(mm[1]):
            a = int(mm[2], 16); rp_fns += 1; in_pack += any(s <= a < e for s, e in pack)
    ledger = sum(1 for l in open('docs/marker-ledger.md') if re.match(r'\|\s*\d+\s*\|', l))
    return dict(pct=pct, units=units, lib_gap=lib_gap, rp_split=100.0 * in_pack / max(rp_fns, 1),
                rp_fns=rp_fns, in_pack=in_pack, named=100.0 * named / max(total_fns, 1), markers=ledger)


# (id, title, measure(M) -> (value_text, done), criterion text)
MILESTONES = [
    ('M0', 'Foundations', lambda M: ('DOL byte-identical, toolchain', True),
     'build/RZTE01_01/main.dol matches build.sha1 from splits; split/symbol recovery and worker tooling in place'),
    ('M1', 'RP framework seeded', lambda M: (f"{M['units']['m1_done']}/28 seeded Pack units ({M['units']['rp_done']}/{M['units']['rp_total']} all Pack)", M['units']['m1_done'] >= 28),
     'all 28 Pack units ported from Wii Sports source are Matching'),
    ('M2', '5% of all code', lambda M: (f"{M['pct']['total']:.2f}%", M['pct']['total'] >= 5),
     'complete (linked) code >= 5% of the DOL'),
    ('M3', 'Library splits complete', lambda M: (f"{M['lib_gap']:#x} bytes unsplit", M['lib_gap'] == 0),
     'no auto (unsplit) code below the game code start; every library file has a split'),
    ('M4', 'RP framework split out', lambda M: (f"{M['rp_split']:.1f}% ({M['in_pack']}/{M['rp_fns']})", M['rp_split'] >= 95),
     '>= 95% of functions with RP framework names (RPSys/RPGrp/RPSnd/RPUtl/...) are inside Pack/ units'),
    ('M5', 'Libraries half done', lambda M: (f"{M['pct']['library']:.1f}%", M['pct']['library'] >= 50),
     'library code (named library units + unsplit library code) >= 50% linked'),
    ('M6', '10% of all code', lambda M: (f"{M['pct']['total']:.2f}%", M['pct']['total'] >= 10),
     'complete code >= 10%'),
    ('M7', 'First sport complete', lambda M: ('manual', False),
     'every unit of one sport (start with Bowling: Pack/RPSports/RPBowScene + its Resort units) is split, named and Matching; mark done by hand in this doc'),
    ('M8', 'RP framework complete', lambda M: (f"{M['pct']['rp']:.1f}%", M['pct']['rp'] >= 100 and M['rp_split'] >= 99),
     'all RP framework code split into Pack/ units and 100% linked'),
    ('M9', 'Libraries complete', lambda M: (f"{M['pct']['library']:.1f}%", M['pct']['library'] >= 100),
     'all library code linked'),
    ('M10', '25% of all code', lambda M: (f"{M['pct']['total']:.2f}%", M['pct']['total'] >= 25),
     'complete code >= 25%'),
    ('M11', 'Every sport split and named', lambda M: ('manual', False),
     'no unk/ units left: every game unit has a proven sport/class directory and file name'),
    ('M12', '50% of all code', lambda M: (f"{M['pct']['total']:.2f}%", M['pct']['total'] >= 50),
     'complete code >= 50%'),
    ('M13', 'Full match, honest', lambda M: (f"{M['pct']['total']:.2f}%, {M['markers']} markers", M['pct']['total'] >= 100 and M['markers'] == 0),
     '100% code and data linked, marker ledger empty (no MATCH-PENDING constructs)'),
]


def table(M):
    rows = ['| ID | Milestone | Status | Now | Criterion |', '|---|---|---|---|---|']
    for i, t, f, crit in MILESTONES:
        v, done = f(M)
        rows.append(f"| {i} | {t} | {'done' if done else 'open'} | {v} | {crit} |")
    rows.append('')
    rows.append(f"Also tracked: game (non-RP) code {M['pct']['game']:.2f}% linked; {M['units']['lib_done']} library units "
                f"Matching; {M['named']:.1f}% of functions named; {M['markers']} MATCH-PENDING marker rows.")
    return '\n'.join(rows)


if __name__ == '__main__':
    M = measures()
    t = table(M)
    print(t)
    if '--write' in sys.argv:
        p = 'docs/milestones.md'; s = open(p).read()
        stamp = f'<!-- STATUS (tools/milestones.py --write, {datetime.date.today()}) -->'
        s = re.sub(r'<!-- STATUS.*?-->.*?<!-- /STATUS -->', f'{stamp}\n{t}\n<!-- /STATUS -->', s, flags=re.S)
        open(p, 'w').write(s)
