# RPUtlRandom::getF32 must be one expression (no iRnd/fRnd locals)

- status: works
- tags: FLOAT,FPR,inline,header,RPUtlRandom,getF32
- scope: include/Pack/RPUtility/RPUtlRandom.h
- source: nm-perm-1

symptom: 99.6-99.9% callers of RPUtlRandom::getF32/getU32(max): lfd magic constant in f2 with f3 temp, orig f3 constant with f1/f2 temps (RPSysKokeshi::LoadResource, RPBowManagerContext::UpdateNpcs, RPGolConfig fn_8029D100)
cause: named u16 iRnd / f32 fRnd locals in the header inline change FPR allocation at every inlined call site; caller-side rewrites cannot move it
fix: return (f32)(u16)(RANDF_MAX & (getU32() >> RANDF_SHIFT)) / (f32)(RANDF_MAX + 1); three functions exact, UpdateMovement 96.4 -> 97.7, 39 NonMatching users no regressions, ninja ok. Dead end: keeping u16 iRnd and dropping only fRnd swaps GPRs in fn_802B9688 and breaks fn_8029DEA8
