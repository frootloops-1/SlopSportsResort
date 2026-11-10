# frsp of a just-stored lfs value comes from an unrolled loop copy

- status: works
- tags: frsp,loop,transpose,matrix,unroll,RPUtl_801C4B7C
- scope: Pack/RPUtility/RPUtl_801C4B7C

symptom: Target stores lfs value to field A, later stores 'frsp fX, sameReg' to field B (matrix transpose / a=b=c in loop); (f32)(f64) casts, f64 locals, double-param inlines, f32-returning accessors all fold away the frsp
cause: MWCC store->load forwarding inside a fully unrolled loop with index vars keeps the forwarded value as double and inserts frsp; straight-line code forwards without frsp
fix: write the copy as a loop: for(int i<3) for(int j<3) tr[i][j]=basis[j][i]; (fn_801C5E38 79->100, fn_801C5F04 96.9->100, fn_801C4C38 93->99.8). Same mechanism as RPBox fn_802FD1A4 loop world[i]=prev[i]=ZERO
