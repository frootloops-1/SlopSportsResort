# fn_801C3574: loop-1 scaffolding shares the prologue block and moves the float schedule

- status: fails
- tags: schedule,fpr,loop,constref,wall
- scope: Pack/RPUtility/RPUtlLytBase/fn_801C3574
- source: claude-sonnet

symptom: Float prologue order differs from retail in two swapped pairs; w/h/ratio inline boundaries, aliasing (__restrict), int/double cast chains and opt pragmas cannot reach it
cause: Loop-1 induction setup (addi r28, mr r29/r30/r27, addi r26, li r25) sits in the same basic block as the float prologue, so its shape feeds the scheduler. opt_strength_reduction off gives [frsp lfs14 stw_a0 fmuls1 lfd_a0] (retail: lfs14 frsp stw_a0 fmuls1 lfd_a0); loop-1 variants without the const-ref views give [lfs14 stw_a0 frsp fmuls1 lfd_a0] (one swap away) but change the instruction count (5 pointers vs retail 6). Loop 2 changes do nothing (different block). The MATCH-PENDING casts in loop 1 reproduce retail GPRs but probably not retail's DAG shape.
fix: none (searched 2026-10-28, ~60 variants, scratchpad v2.py/v3.py): per-site const views (C-style/static_cast const T&, *static_cast<const T*>(&x), static_cast<const Vec*>, const-ref array aliases, nw4r::math::VEC3Normalize with/without cast, pointer-offset forms, field-wise and VEC3-base copies, tn with &x / x+i) give only two schedule classes. Every variant with the 162-instr layout (both the normalize-src and transform-in const views present) has our schedule [stw_a0 frsp lfs14 lfd_a0 fmuls1]; every variant with fewer views (158/160 instrs) has [lfs14 stw_a0 frsp fmuls1 lfd_a0]. Retail's [lfs14 frsp stw_a0 fmuls1 lfd_a0] with 162 instrs is not reachable by loop-1 spelling. VEC3Normalize alone does not create the const view; its inline param keeps the plain pointer. Unit stays parked; the remaining difference is outside loop 1.
