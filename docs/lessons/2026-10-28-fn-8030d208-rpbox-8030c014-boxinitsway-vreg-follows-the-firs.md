# fn_8030D208 (RPBox_8030c014): BoxInitSway, vreg follows the first definition, not the declaration

- status: fails
- tags: regalloc,fpr
- scope: RPBox_8030c014 fn_8030D208
- source: FPR batch 2 2026-10-28

symptom: 99.86
cause: target colours the random values before the interpolation results; computing speed before a adds saved f25 (91.6); declare-up-front does not move a vreg
fix: none: BoxSetSpeed inline (91.6), up-front decl, invented param helper, named amp (97.7). park
