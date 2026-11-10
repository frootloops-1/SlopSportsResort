# RPUtl_801C73B0 fn_801C76D0: uniform inline decode helper fixes FP colouring

- status: works
- tags: Record,unpack,dequantize,fpr,colouring,post-RA,scheduler,inline-helper
- scope: Pack/RPUtility/RPUtl_801C73B0

symptom: unpack (s16/s8 field * scale -> Vec/Quaternion) 16-40 diff lines: stfs/lfd order swapped, FPR numbers differ, pre-RA schedule (mwcc_dbg backend-02) already identical to retail
cause: FPR colouring: retail needs y*s and qx*s to colour last (f3); different regs then make the post-RA scheduler (between backend-05 and 07) move a stfs/lfd pair. Not a pre-RA order issue. Direct t->x = (s16)x*scale stores colour them early.
fix: Route every field through one static inline helper: static f32 dequantize(s16 v, f32 s){return v*s;} (template/int/f32-cast variants also match; helper only on t or only on q does not). Also: named temps ty+vx in natural x,y,z order match. Changing fields u16->s16 regresses fn_801C7414.
