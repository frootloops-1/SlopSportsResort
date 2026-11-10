# Split a one-file unsplit source by symbol address; duplicate prelude, add cross-TU prototypes

- status: works
- tags: split,source,unsplit,rpsportscommon
- scope: RPSportsCommon_unsplit

symptom: A blob with ~11k lines of matched source must be split into per-TU objects without losing function matches
cause: Source interleaves types, externs, pragmas and defs; one object per source file
fix: Parse decl-level items, assign function/data defs by symbols.txt address vs splits.txt section ranges, copy whole prelude + referenced static helpers to each TU, emit prototypes for callees now in other TUs at their old position; recompare per-function scores vs a saved baseline (427 -> 433 exact, 0 regressions)
