# Forecast lever 1 (declaration order of named locals) cannot fix fn_802DFC10 case-1 r31/r30 pointer

- status: fails
- tags: forecast,regalloc,gpr,declaration-order
- scope: RPBox_802de63c fn_802DFC10
- source: forecast-regalloc

symptom: case-1 strength-reduced pointer r31 vs target r30 (fn_802DFC10, RPBox_802de63c)
cause: the pointer is a compiler @/SR temp, not a named local; reordering i/modelSelf/x/j only perturbs case 0 colouring
fix: 3 hand-picked orders: x,modelSelf,i,j flat (4 lines); j,i,modelSelf,x 98.6; modelSelf,i,x,j 99.2. Lever 7 (reuse x as the induction pointer) closed it instead
