# RPBsb_80275a44: per-record pointer temp (3rd confirmation), FPR swap via named reload, 206 sdata2 externs -> literals

- status: works
- tags: pointer-temp,block-split,fpr-colouring,sdata2,pool-order,literals,RPBsb_80275a44
- scope: Pack/RPSports/RPBsbScene
- source: claude opus worker 2026-11-02

symptom: fn_80278D34 98.6 (BsbStateClearKeepBase hack); fn_80275E34 99.6 f4/f2 swap; .data 43.75 .sdata/.sbss/.sdata2 0
cause: block-split mechanism as fn_8027FB5C (14 records); frsp value from forwarded member reload into an inline param was an expression temp with a higher vreg than a, coloured first
fix: { BsbPmfHolder* s = &self->st[i]; s->Init(); } x14; declare f32 a; f32 b; first and add named reload f32 u = self->f38C passed to the inline (vreg order u<t<b<a). Data: replace 206 extern lbl_804C3xxx with float literals (pool_renames.py --unit ... --apply; adding literals renumbers later @N, so rerun after final source and renumber existing @N data symbols); BsbVec3 a = {c1,c2,c3} becomes a .rodata copy so use field-wise set; 1.0f*x folds, so store constants then named f32 s and *= s; dead (void)0.1f;(void)0.0f; seeds pool head (ledger 98); 89 .sdata values via SDATA_CONST (ledger 99). Byte-compare .sdata2 against the DOL since objdiff ignores order
