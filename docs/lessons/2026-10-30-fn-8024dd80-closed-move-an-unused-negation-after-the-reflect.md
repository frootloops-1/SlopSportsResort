# fn_8024DD80 closed: move an unused negation after the reflect block, verified with mwcc_dbg colouring

- status: works
- tags: fpr,colouring,vreg-order,mwcc_dbg,RPTns
- scope: Pack/RPSports/RPTnsScene/RPTns_8024dc50

symptom: fn_8024DD80 98.3: ~10 FPR renames in the mirror/reflect block
cause: FPRs are coloured in descending vreg order. The target needed negD (r2.z, which is never read again) coloured before the frsp temp of the dot product, so its vregs had to be created later. It also needed the r1.z load/neg coloured before the r0.x load
fix: statement order pos.z, r0.x, r1.z negations, then dot + reflect, then 'self->rot.r2.z = -self->rot.r2.z;' last -> 100, no markers. The earlier 6 orders all kept the 4 negations ahead of the dot. Method: map each vreg from backend-02-before-regalloc.txt to its target register, then find which vreg must be coloured earlier
