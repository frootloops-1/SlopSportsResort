# RPGol_802c68a4 closed: const input plus post-restart index read creates the required backend temp

- status: works
- tags: rpgol,802c698c,const,alias,backend,regalloc,flip
- scope: Pack/RPSports/RPGolScene/RPGol_802c68a4
- source: codex-gol698c-1102, base 2934560e4

symptom: 5/6 functions exact; fn_802C698C 99.84456 with five wrong register operands: conversion r0 and cached index r3 versus retail conversion r3/index r0.
cause: Cached int n is named vreg r35, older than backend conversion r97/r98, so conversion gets r0 first. Reading the index after restart creates backend load temp r101, newer than conversion r96/r97; it gets r0. Const GolLytArg* allows that load to hoist to the retail slot despite its later source position. Both changes are required.
fix: Change declaration/definition arg to const GolLytArg*. Delete int n = arg->idx; keep a->restart(); then s->idx = arg->idx; as ordinary statements. Const alone is unchanged; non-const comma98.73057; const+comma100; simpler const+separate statements100. Six GC builds agree. Debug-final confirms r101->r0, r96/r97->r3. Unit6/6 and every section100; no new markers; FLIP-OK DOL0 only three known collisions. Evidence /private/tmp/ogws-gol698c-1102/build/evidence/gol698c/.
