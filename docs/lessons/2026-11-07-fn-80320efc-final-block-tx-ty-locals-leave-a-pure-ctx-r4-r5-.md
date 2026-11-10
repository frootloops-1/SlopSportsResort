# fn_80320EFC final block: tx/ty locals leave a pure ctx r4/r5 register residue

- status: works
- tags: mwcc,regalloc,fn_80320EFC,RPBow
- scope: Pack/RPSports/RPBowScene/RPBow_80320EFC

symptom: inline Set(ctx->vA0.x, ctx->vA0.y) loaded .y before .x (inline args evaluated right to left); ctx also r4 vs r5
cause: MWCC evaluates inline-call arguments right to left; named f32 locals fix the load order
fix: f32 tx = ctx->vA0.x; f32 ty = ctx->vA0.y; Set(tx, ty): objdiff improves slightly, residue is only the ctx register
