# 12-byte float snapshot copies: union whole-copy gives lwz/lwzu words

- status: works
- tags: mwcc,struct-copy,golball
- scope: RPGolMapObjBall fn_80299528
- source: claude/golball-c-1107 4b67b8cd0

symptom: Retail copies a 3-float vector snapshot with lwz/lwzu/stw; GolBallVec3/VEC3/Vec copies emit lfs/stfs
cause: MWCC copies small all-float structs memberwise with FP regs; a union with an s32 view copies as words; member .w = *(Words3*) loses the lwzu base form
fix: pos = *(GolBallV3Bits*)self->target; hit = *(GolBallV3Bits*)&global; (whole union) -> fn_80299528 100%
