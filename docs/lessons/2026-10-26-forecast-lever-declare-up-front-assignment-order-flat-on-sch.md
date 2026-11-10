# Forecast lever: declare-up-front/assignment order flat on scheduling-only diff

- status: fails
- tags: forecast,regalloc,declaration-order,scheduling
- scope: RPBsb_80252e7c/fn_80254AAC
- source: forecast-regalloc

symptom: two lfs swapped in order (scheduler), registers already right
cause: diff was alias-driven schedule, not vreg colouring; declaration order swaps regs (f0/f1) but never the load order
fix: none from levers 1,2,6,8,9; real fix was const on the global (alias)
