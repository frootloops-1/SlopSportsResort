# fn_802A7CD8 FPR permutation (99.4) and fn_802A8850 r26/r27 swap (99.7)

- status: open
- tags: regalloc
- scope: RPGol_802a7a40
- source: fn_802A8850

symptom: saved reg permutation
cause: unknown
fix: dead ends: decl permutations, non-inline b, split clamps, len scope/expr, filter inline; try permuter
