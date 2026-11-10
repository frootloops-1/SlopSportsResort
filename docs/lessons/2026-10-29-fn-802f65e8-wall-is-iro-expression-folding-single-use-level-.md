# fn_802F65E8 wall is IRO expression folding: single-use 'level = elem->level' folded into tbl[level]

- status: fails
- tags: RPBox_802f5a6c,IRO,propagation,regalloc
- scope: RPBox_802f5a6c

symptom: 99.6%: level vreg r66 > tbl temps r61..r65 so it takes r0; target has tbl[0]=r0, level=elem=r10
cause: IroPropagate_PropagateExpressions folds a one-read local inside one IRO basic block at the start of both optimizer passes, so the load is generated after the tbl copy. #pragma opt_propagation off makes volatile regs match but shifts callee-saved (98.5). A real branch or second read keeps level as r33.
fix: Parked after ~30 variants. Nearest: else body wrapped in for(int j=0;j<1;j++) after 's32 level = elem->level;' keeps the split (lwz r10,0x3e4(r10) matches) but IRO hoists &tbl and the shift index goes early: 98.5. Needs a construct that splits IRO blocks and leaves no code (would be an R17 marker). Reference: ~/Downloads/mwcc-cuyler36/src/optimizer/IroPropagate.c, IrOptimizer.c 284-390.
