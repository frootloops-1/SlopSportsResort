# fn_802F77C8 (RPBox_802f71b0): up-front uninitialised declarations reach half the registers, ax.z/step stay off

- status: fails
- tags: regalloc,fpr
- scope: RPBox_802f71b0 fn_802F77C8
- source: FPR batch 2 2026-10-28

symptom: 99.50; tail chain-init block with >=10 interacting FP values
cause: declare f32 x0,y0,x1,y1,len,z0,z1,step up front + step=-len gets ax.x/ax.y/len/z0/x0 right but ax.z f0 (target f8), step f8 (f9); struct-member loads and result-takes-dying-source-reg do not follow the vreg model
fix: none: inline SbInitChain with f32 len param folds -len into a new pool constant (98.5); ax = SbGetUp(&mm2) collapses the frame (94.1). gain too small to keep
