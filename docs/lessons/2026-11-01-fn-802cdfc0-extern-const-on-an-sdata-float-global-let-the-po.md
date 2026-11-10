# fn_802CDFC0: extern const on an .sdata float global let the post-RA scheduler hoist its lfs

- status: works
- tags: const,sdata,post-ra,fn_802CDFC0,RPBox
- scope: Pack/RPSports/RPBoxScene/RPBox_802cb9cc
- source: unit sweep 2026-11-01

symptom: 99.8%; exact FPR colours reachable but lfs step hoisted into the prologue (96.3)
cause: extern const f32 on a writable .sdata symbol gives the load no dependencies so the post-RA scheduler floats it after mflr; other units declare it non-const
fix: extern f32 lbl_804BDC30 (non-const) + int t first; f32 remaining; f32 step = lbl; remaining = f2C; remaining -= step; f2C = remaining. Check the symbol section before keeping const on extern float globals. Dead with non-const: self->f2C -= lbl, step-first + f2C -= step, remaining-init-first, other statement orders
