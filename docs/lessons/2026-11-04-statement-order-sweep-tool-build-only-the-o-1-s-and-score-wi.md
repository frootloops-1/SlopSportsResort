# Statement-order sweep tool: build only the .o (~1 s) and score with asm_diff; 700+ variants in minutes

- status: works
- tags: sweep,tooling,regalloc,pre-ra-schedule
- scope: Pack
- source: claude/sp801ef-1103

symptom: register/colour walls where the final instruction order already matches
cause: MWCC schedules before and after regalloc; vreg numbering and the pre-RA order decide colours and are invisible in the final asm
fix: scratch/sweep.py in the sp801ef-1103 worktree: JSON groups of contiguous statements, cartesian product of permutations, ninja the single object + asm_diff count. Also sweep variable shapes (named vs expression, reuse a counter, loop form), not only order. Closed fn_801EF2F0 (24 orders), fn_801EF4B8, fn_801F0B24
