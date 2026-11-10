# fn_802D3CF8: t-first BoxLerp, w680 write first, named fc, inline sign close all FPR + w680; 100 -> 44 lines, GPR b/flags/h open

- status: open
- tags: fn_802D3CF8,RPBox_802cf93c,regalloc,mwcc_dbg
- scope: RPBox_802cf93c

symptom: BoxLerpABT blocks t f5/b f0 vs f0/f5; g compare const f2 vs f0; v468 b copy f4/f2/f5; w680 r0/r3; then GPR b r6 vs r3, flags r3 vs r4, h r9 vs r10
cause: inline param vregs are created in argument order and earlier-created @ gets the higher vreg, coloured first: BoxLerp(t,a,b) makes t the first-coloured (f0). A named f32 coloured last gives the 0.0f const the low reg. Statement order sets creation order of the 7 and w680 loads. GPR: b is a named local (coloured after the in.flags/h front-end temps r44/r43), target has b r3 first; declaring b earlier/at function top does not change the colours
fix: kept: BoxLerp(self->f420, v.x, self->v414.x) x3; w680 &= ~4 before w4D8 = 7; f32 fc = owner->f3CC; (f32)lbl_804C4E08[w148] * b.x inline (no sign local). Dead: BOOL b as inline helper (156 lines), repeated || / !&& expression twice (163), b declared before o5 or at function top (no change), g compare swap
