# fn_8030F8C4 (RPBox_8030c014): threshold blocks, local reorders flat, expression forms change the schedule

- status: fails
- tags: regalloc,fpr,schedule
- scope: RPBox_8030c014 fn_8030F8C4
- source: FPR batch 2 2026-10-28

symptom: 98.95
cause: folding lerps or p into the comparison changes the instruction order
fix: none: one-expression threshold (98.5), mx before mirrored (98.8), all locals up front, p inlined (94.9). park
