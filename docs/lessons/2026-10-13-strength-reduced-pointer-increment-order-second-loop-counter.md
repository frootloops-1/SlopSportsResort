# Strength-reduced pointer increment order: second loop counter j for the table that must increment last

- status: works
- tags: strength-reduction,loop,increment-order,second-counter
- scope: Pack/RPKernel/RPSysPauseMenu

symptom: pointer increments at loop end in wrong order (98.1)
cause: MWCC creates derived pointers in evaluation order; j-indexed table handled after i-based
fix: for(int i=0,j=0;i<3;i++,j++) tbl[j] for the table whose increment must come last; j optimised away
