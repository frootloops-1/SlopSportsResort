# forecast lever 1 (declare-up-front order) fails on fn_801E8ED0 and fn_801F0020

- status: fails
- tags: forecast,regalloc,declare-order
- source: forecast-regalloc

symptom: single-value register rename (r27 vs r28; r0/r4 swap) in a 99.9% function
cause: declaration position only moves a named local among callee-saved regs (r27 before a nested loop, r25 after) and never reaches the target colour when the target value was an inline @-variable or a float-typed result
fix: do not sweep decl positions; check first whether the value came through an inline getter/helper (lever 3 family) or a differently typed named result (lever 8). Lever 1 did work on fn_8020489C where the target shared one named local across two branches
