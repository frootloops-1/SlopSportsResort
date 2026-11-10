# Milestones (Wii Sports Resort, RZTE01_01)

Project-level goals, in the order we expect to reach them. Each has a measurable criterion; `tools/milestones.py`
measures them from the objdiff report, the splits and the marker ledger. Update the table after merging a batch:

```sh
ninja build/RZTE01_01/report.json && python3 tools/milestones.py --write
```

The phases in `docs/decompilation-roadmap.md` say *how* to work; these milestones say *what counts as progress*.
Pick work that moves the next open milestone, without skipping a cheaper earlier one.

<!-- STATUS (tools/milestones.py --write, 2026-11-09) -->
| ID | Milestone | Status | Now | Criterion |
|---|---|---|---|---|
| M0 | Foundations | done | DOL byte-identical, toolchain | build/RZTE01_01/main.dol matches build.sha1 from splits; split/symbol recovery and worker tooling in place |
| M1 | RP framework seeded | open | 17/28 seeded Pack units (18/55 all Pack) | all 28 Pack units ported from Wii Sports source are Matching |
| M2 | 5% of all code | open | 3.29% | complete (linked) code >= 5% of the DOL |
| M3 | Library splits complete | open | 0x69958 bytes unsplit | no auto (unsplit) code below the game code start; every library file has a split |
| M4 | RP framework split out | done | 96.7% (557/576) | >= 95% of functions with RP framework names (RPSys/RPGrp/RPSnd/RPUtl/...) are inside Pack/ units |
| M5 | Libraries half done | open | 12.2% | library code (named library units + unsplit library code) >= 50% linked |
| M6 | 10% of all code | open | 3.29% | complete code >= 10% |
| M7 | First sport complete | open | manual | every unit of one sport (start with Bowling: Pack/RPSports/RPBowScene + its Resort units) is split, named and Matching; mark done by hand in this doc |
| M8 | RP framework complete | open | 16.6% | all RP framework code split into Pack/ units and 100% linked |
| M9 | Libraries complete | open | 12.2% | all library code linked |
| M10 | 25% of all code | open | 3.29% | complete code >= 25% |
| M11 | Every sport split and named | open | manual | no unk/ units left: every game unit has a proven sport/class directory and file name |
| M12 | 50% of all code | open | 3.29% | complete code >= 50% |
| M13 | Full match, honest | open | 3.29%, 3 markers | 100% code and data linked, marker ledger empty (no MATCH-PENDING constructs) |

Also tracked: game (non-RP) code 0.00% linked; 95 library units Matching; 17.4% of functions named; 3 MATCH-PENDING marker rows.
<!-- /STATUS -->

## Notes per milestone

- **M1 RP framework seeded**: the 28 `Pack/` units already split (`docs/tasks/game-code.md` lists what blocks each).
  Shared headers (RP, EGG) get Resort layouts with evidence addresses; one writer per shared header at a time.
- **M2 / M6 / M10 / M12**: "complete" = linked code (objdiff `complete_code`), the number that counts. Functions
  that only match through MATCH-PENDING markers count here but are reported separately (`docs/marker-ledger.md`).
- **M3 Library splits**: the remaining unsplit library code is newer-SDK/NW4R/EGG files without a reference split;
  place them from neighbour order, strings and object order (`tools/carve_unk.py --gaps`, `docs/symbol_recovery.md`).
- **M4 RP framework split out**: most framework code still sits in `unk/` units. Carve it with names from
  `fuzzy_match.py` and ogws `src/Pack` file order; check each file's real start/end (lesson: name-matched splits start
  at the first *named* function).
- **M5 / M9 Libraries**: port from ogws (`docs/porting.md`, `port_sizecheck.py`), then forecast/ss sources for newer
  files; Resort's EGG is newer than ogws's (layouts in `include/egg` carry Resort evidence).
- **M7 First sport**: Bowling first (Resort keeps Wii Sports' `Pack/RPSports/RPBowScene` code plus its own units).
  Decide the sport directory naming when the first sport is split, record it in `docs/sport_map.md`. Mark done here
  by hand (the script cannot tell which units belong to a sport yet).
- **M11**: every `unk/sinit_*` / `unk/text_*` unit replaced by a proven file; names only from strings, vtables, RTTI or
  a matched Wii Sports counterpart (placeholders otherwise).
- **M13**: the honesty policy's end state: every MATCH-PENDING marker replaced by plausible original source.

## Baseline (2026-11-09, when milestones were set)

3.07% of all code linked (209,128 / 6,574,604 bytes); 95 library units and 9 RP units Matching; library code
(named + unsplit) 1.6 MB, of which 0x69958 bytes not yet split; 4.8 MB of game code in 374 `unk/` units.
