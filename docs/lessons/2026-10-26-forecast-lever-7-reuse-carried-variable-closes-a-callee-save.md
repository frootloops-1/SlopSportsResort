# Forecast lever 7 (reuse carried variable) closes a callee-saved r31/r30 swap on a strength-reduced loop pointer

- status: works
- tags: forecast,regalloc,gpr,induction,strength-reduction,loop
- scope: RPBox_802de63c fn_802DFC10
- source: forecast-regalloc

symptom: unrolled 1-iteration loop pointer addi r30,r3,0x1c in target, ours r31 (fn_802DFC10 case 1)
cause: MWCC merges the strength-reduced self->models[i] pointer into a named pointer variable that is an equivalent induction var; reusing the case-0 variable x (r30 colour slot) instead of a fresh one changes its colour
fix: x = (BoxX*)((u8*)self + 0x1c); for (i = 7; i < 8; i++, x = (BoxX*)((u8*)x + 4)) {...self->models[i]...}; must start at the exact SR base (x = self fails). Marked MATCH-PENDING (R17), ledger row 19. Plain loop, fresh j/k index, modelSelf=self all stay r31
