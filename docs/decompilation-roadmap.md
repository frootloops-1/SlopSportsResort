# Decompilation roadmap (Wii Sports Resort, RZTE01_01)

## Phase order

Milestones (what counts as progress, measured): `docs/milestones.md`, `python3 tools/milestones.py --write`.

Work the phases in order; inside a phase, pick by flippability (units one function or one data fix from Matching first).
Each phase feeds the next: library matches give headers and names, the RP framework gives the classes every sport uses.

| # | Phase | Source of truth | Main tools | Status 2026-11-09 |
|---|---|---|---|---|
| 0 | Project setup: splits, names, data ownership | dtk analysis, ogws, riptl RZTP01, other decomps | `docs/symbol_recovery.md` pipeline | done (re-run passes after big naming changes) |
| 1 | Libraries: RVL SDK, NW4R, EGG, MSL, MetroTRK, BTE, RFL, HBM | ogws source (CC0), forecast/ss/mkw splits | `port_scan.py` -> `port_flip.py` -> gates (`docs/porting.md`) | 82 units Matching; 48 more scanned exact but blocked (`docs/tasks/libraries.md`) |
| 2 | RP framework (shared with Wii Sports: `RPSys*`, `RPGrp*`, `RPUtl*`, `RPSnd*`) | ogws `src/Pack`, then Resort asm | port per unit, then match by hand | 1 unit Matching (`RPGrpDrawPathShadowTexture`) |
| 3 | Resort game code, sport by sport | Resort asm only | workers per unit; `fn_asm`/`fn_diff` | started: Basketball `unk/sinit_8051B8B4.cpp` 6/11 exact |
| 4 | Finishing: data sections, flips, names, split refinement | everything | `unit_cmp`, `flip_gate`, `vtable_check` | ongoing |

### Phase 1 detail (libraries)
1. Fix the 19 units that only compile on Wii/1.0 with scratch workarounds: make the ogws headers Wii-compiler clean
   (float constant expressions, `offsetof` constants, access checks, C typedef redeclarations). Header edits must keep
   every Matching unit Matching.
2. Units whose data could not be located from `.text` relocations: locate from data references (vtables, tables).
3. Units scanned "near" (>= 80%, no missing functions): route as tier C.
4. Newer-SDK files Resort has but ogws lacks: start from `doldecomp/forecast` (RVL SDK) or `zeldaret/ss` (NW4R/EGG) source.

### Phase 2 detail (RP framework)
- Only 9 ogws Pack units have Resort splits; the rest of the framework sits in `unk/` and auto units. First split it:
  run `tools/port_splits.py` with the RP names (lower coverage threshold, checked by hand), then port unit by unit.
- Expect layout changes (e.g. `RPGrpView` gained a member at 0x1C). Change a shared header only together with every
  unit that includes it, and re-run the DOL gate.

### Phase 3 detail (sports)
- Order: smallest self-contained sports first (`docs/sport_map.md`): Wakeboarding, Bowling, Archery, Power Cruising,
  then Basketball, Table Tennis, Frisbee, Canoeing, Cycling, Air Sports, Golf/Frisbee Golf, Swordplay.
- Per unit: name the class from its vtable/RTTI/strings when proven, otherwise placeholders; write functions
  last-first (reverse emission); rename symbols to the mangled names; flip when all functions and data match.
- When matching shows where one source file ends inside an `unk/` unit, split the unit (keep the DOL gate green).

## Resort differences from ogws (read before reusing an ogws lesson)
- Game code: Wii/1.3, optimise-for-size pragma, `-func_align 4`. ogws game code is GC/3.0a5.2 at `-O4,p`.
- Resort math is paired-single NW4R (`VEC3Sub/Scale/Len` inline asm); ogws EGG vector ops are scalar.
- `.BINARY` section (embedded Yaz0 archive) at 0x80654560, as in ogws.
- Weak inline copies are spread through each unit (not at its end); `__sinit` is always a unit's last function.

## Picking a batch
`python3 tools/route_functions.py summary --limit 15`, `python3 tools/unit_cmp.py <unit>`; then the phase table above.
