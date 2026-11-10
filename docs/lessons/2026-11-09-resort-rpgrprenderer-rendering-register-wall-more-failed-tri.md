# resort: RPGrpRenderer Rendering register wall, more failed tries

- status: fails
- tags: resort,regalloc,RPGrpRenderer
- scope: resort
- source: rp9b-renderer

symptom: Rendering 98.4: identical instructions, consts 1/2 take r30/r31 vs r22/r23; Configure temps r3/r4 swapped; sole flip blocker (70 DOL bytes)
cause: callee-saved colouring order differs
fix: failed (in addition to batch 9's four): local option evaluated before Configure, capture declared at function top, direct mEnable/mOption stores (worse)
