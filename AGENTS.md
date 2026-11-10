# Agent instructions

Target: Wii Sports Resort USA Rev 1 (`RZTE01_01`, disc revision 1). Original disc image in `orig/RZTE01_01/`
(dtk reads `sys/main.dol` from it); symbols and splits in `config/RZTE01_01/`; source in `src/`, headers in `include/`.
Sister project: Wii Sports, `~/Downloads/ogws-master` (`RSPE01_01`). Much of Resort's library and RP framework code
is shared with it; its source, headers and lessons are the first place to look.

## Read order (stop as soon as you have what you need)

1. This file.
2. `docs/decompilation-roadmap.md`: phases, current state, how to pick targets.
   `docs/milestones.md`: project goals M0-M13 and their live status (`python3 tools/milestones.py`); pick work that
   moves the next open milestone.
3. `docs/matching-playbook.md`: what pays off, the batch procedure, the honesty policy (written on ogws; it applies
   here, with the Resort differences listed in the roadmap).
4. `docs/tasks/<component>.md`: **"Current state" section only**.
5. `python3 tools/lessons.py search <terms>` before any experiment. The library holds ~1900 ogws lessons (same compiler
   family) plus Resort ones; prefer lessons dated after 2026-11-08 or tagged `resort` when they conflict.
6. Register-only walls: `docs/regalloc-playbook.md`, `docs/llm_matching_tricks.md`.
7. Symbol/split recovery history and tools: `docs/symbol_recovery.md`, `docs/porting.md`, `docs/sport_map.md`.

## State

Day-0 project (started 2026-11-08). No map, no debug build. 96 units Matching (library code ported from ogws plus one
RP framework unit), ~2% of code. Names: ~5,500 of 34,167 functions (ogws signatures and fuzzy matching, riptl
`RZTP01.txt`). Units: 868 split (491 named, 377 `unk/`); game code mostly `unk/sinit_<addr>.cpp` (end exact, start an upper bound)
or `unk/text_<addr>.cpp` (code between a carved library file and the previous boundary; both ends exact, may hold several files).
Data is assigned to units (`.data` 85%, `.sdata2` 92%, `.bss` 34%). Numbers: `ninja progress`.

## Compiler and flags (per unit input; check before any wall)

| Code | `mw_version` | Notes |
|---|---|---|
| RP framework + Resort game code (`RP`, `Sports2` libs) | **Wii/1.3** | ogws `cflags_rp` + `-func_align 4` + `-pragma "optimize_for_size on"`, SportsPack PCH |
| NW4R, EGG, RVL SDK, MSL (ported) | Wii/1.0 or the unit's ogws version | per object in `config/RZTE01_01/ported_objects.json` |
| BTE (Bluetooth), RVLFaceLib | GC/3.0a5 / GC/3.0a5.2 | prebuilt older libraries, byte-identical to Wii Sports |
| Linker | Wii/1.0 | |

Evidence: `tools/compiler_sweep.sh` (library units), the size-mode finding in `docs/tasks/game-code.md`.
`-DVERSION_RSPE01_01` is defined so ogws headers take their Wii Sports Rev 1 branches.

## Worktrees and integration

- Source edits happen in a task worktree on a unique branch off `main` (`tools/setup_worktree.sh <dir> <branch>`,
  dirs under `/private/tmp/wsr-*`), one worktree per worker. Never two builds in one tree.
- One writer per unit and per shared file (`configure.py`, `ported_objects.json`, shared headers). Workers may rename
  `fn_XXXXXXXX` lines in `config/RZTE01_01/symbols.txt` only for functions of their own unit (objdiff pairs by name).
- The orchestrator merges one branch at a time into `main`: `ninja` ends with `build/RZTE01_01/main.dol: OK`,
  `tools/dol_diff.py` reports 0 bytes, `tools/sym_addr_check.py` reports 0 moved symbols, `verify.py` shows no
  regression. Flip a unit to Matching only after that, one unit at a time (`tools/flip_gate.py`).
- Local merges into `main` are authorized. Pushing, remote merges, history rewrites and PRs are not. The repo's
  `origin` is still `encounter/dtk-template`: never push there.

## Evidence and verification

- Original bytes are the authority. Map names (RZTP01, Dolphin) and fuzzy matches are evidence: validate address and
  size before importing, and keep placeholder names (`Unk_<addr>`, `mUnkXX`, `unk/sinit_<addr>.cpp`, `unk/text_<addr>.cpp`) for anything not
  proven by strings, vtables, RTTI or a matched Wii Sports counterpart.
- Capture a baseline (`verify.py <unit> --save`), change, compare again, preserve existing matches.
- Report function matches, section scores and whole-object status separately. objdiff 100% is not a match until the
  DOL link passes. Mark Matching only when code, data, relocations and layout all check out.
- Compiler-steering constructs are a last resort under the honesty policy (`// MATCH-PENDING (R17)` plus a row in
  `docs/marker-ledger.md`).

## Commands (repo root; output is capped)

```sh
python3 tools/fn_asm.py <fn>                      # one function's asm with float/string constants
python3 tools/fn_diff.py <unit src path> <fn>     # rebuild one object, normalised diff of one function
python3 tools/obj_score.py <obj> orig/RZTE01_01/sys/main.dol config/RZTE01_01/symbols.txt -v   # exact fns
python3 tools/verify.py <unit> --save | -v        # baseline / compare (objdiff report)
python3 tools/asm_diff.py <unit> [fn] -n 30
python3 tools/unit_cmp.py <unit>                  # per-section state: flip-candidate check
python3 tools/flip_gate.py <unit> [--keep]        # temp-flip + DOL/sym gate
python3 tools/route_functions.py summary|unit|next|record
python3 tools/lessons.py search|add ...
ninja && python3 tools/dol_diff.py && python3 tools/sym_addr_check.py
python3 tools/dol_blame.py orig/RZTE01_01/sys/main.dol build/RZTE01_01/main.dol config/RZTE01_01/splits.txt  # which unit broke the DOL
```

Porting library units from ogws: `docs/porting.md` (port_scan -> port_flip -> fix passes -> gate).

## Output discipline

Never print whole `.s` files, objdiff JSON or full ninja logs; pipe through `head`/`tail`/`cut`. A diff that needs
more than ~40 lines goes to a routed worker that returns only its json block.

## Checkpoints

- Commit coherent, verified changes; a partial unit says "not a full match".
- Handoff: `docs/tasks/<component>.md`, "Current state" first, under ~40 lines.
- Record each verified win or dead end: `python3 tools/lessons.py add ...` (mention `resort` in the title).
- Never commit the disc image, build output or Ghidra databases.
