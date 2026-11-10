# Deg-to-rad as inline d*lbl_804C1A20 fixes float reg swap

- status: works
- tags: regalloc,float,inline,constant
- scope: Pack/RPSports/RPTnsScene/RPTns_80220994
- source: worker 2026-10-15

symptom: fn_802228D4 99.4%: 140.0f and pi/180 const loaded with f1/f2 swapped (fmuls f1,f1,f2 vs f2,f2,f1)
cause: original used an inline helper per product; locals c/k, operand order, temps, reversed stores, direct 140*lbl all leave the swap
fix: static inline f32 tnsDeg(f32 d){return d*lbl_804C1A20;} self->f68=tnsDeg(140.0f); self->f6c=tnsDeg(10.0f) -> exact
