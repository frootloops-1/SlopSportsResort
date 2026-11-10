# Calculate (PlayerSelect) register residue dead ends; mwcc_dbg colouring rule

- status: fails
- tags: regalloc,mwcc_dbg,RPSysPlayerSelectScene,colouring-order
- scope: Pack/RPSports
- source: claude opus worker 2026-11-02

symptom: Calculate 99.8: state-2 result r30 vs r29, calcState11 loop1 ptr r29 vs r27, loop2 i/p710 r27/r28 vs r28/r27
cause: Colouring is descending vreg number; each node takes the lowest already-used callee-saved reg free of conflicts, else next new reg down from r31. r is an early codegen temp (r60) above idx16 (r47). Target order would be mii > idx16 > r > i2 > p710 > ptr > i1
fix: Not found. Dead: separate loop counters/j, p710 declared early or outside loop, s32 idx16, idx16 static-inline getter (99.7; as arg 97.4), r at function top / inline helper / BOOL, regsearch --generic 10 min 331 evals rank 4
