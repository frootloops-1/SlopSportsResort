# fn_80200600 closed: fn-level decls put a/else-IV between row r and counter i; named struct-typed walk replaces the compiler IV

- status: works
- tags: regalloc,color_sim,numbering,webs,induction,RPSports_801ffec0
- scope: Pack/RPSports
- source: claude/sp801ff-1103

symptom: two-branch a r28 vs r29, else-loop IV r30 vs r29 (6 rows, 99.9)
cause: colour order is descending vreg for low-degree nodes; named locals numbered in declaration order, a 2nd web of a variable is renumbered above the locals, compiler IVs above everything; retail needs a and the else pointer between r (r29) and i (r28)
fix: after flags: SpPlyrRowLyt* r; SpAnm2* a; SpRowListSelf* q; a used ONLY in the two branch (first-branch keeps its own local), r used in first and last loops; else loop q = (SpRowListSelf*)((SpPlyrRowLyt**)self + i); do { q->rows[0]->pVirt->v4(); q = (SpRowListSelf*)((SpPlyrRowLyt**)q - 1); } -> 100, FLIP-OK. SpPlyrRowLyt** walk gives addi 0x70 (99.6). R17 ledger 159
