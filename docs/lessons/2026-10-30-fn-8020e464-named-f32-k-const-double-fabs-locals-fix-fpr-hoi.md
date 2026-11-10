# fn_8020E464: named f32 k const + double fabs locals fix FPR hoist order; e.a needs a named local below i

- status: works
- tags: fn_8020E464,RPSports_8020b294,vreg,colour,fpr,gpr,named-local,mwcc_dbg
- scope: Pack/RPSports/RPSportsCommon/RPSports_8020b294

symptom: loop body identical, FPR hoisted consts f6/f7/f8/f2 vs target f5/f6/f7/f8, GPR loop regs ptr/i/4330/f4/a r7/r8/r5/r4/r3 vs r6/r7/r4/r3/r8; fabs and frsp shared one reg
cause: mwcc_dbg: hoisted LICM const kept its loop-body vreg (high) so it was coloured first; named locals are numbered in reverse declaration order below temps; target colours e[i].a last so it must be a named local numbered below i; absf inline does frsp in place on the fabs vreg
fix: f32 k = lbl_804C2308; declared after h before the loop (k vreg < h) -> FPR f5..f8 right; double dw = __fabs(b - a); f32 w = dw; (same for h) -> fabs f2 / frsp f6,f2 split; 88.7 -> 92.1 no markers. 's32 av = l->e[i].a; av = av & 0xFFFFFFFF;' (R17 marker, NOT committed) makes every GPR match -> 93.9; plain/-=20/(s32)/register/av=0;av+= /inline-helper spellings are propagated by IRO (92.1-93.8).
