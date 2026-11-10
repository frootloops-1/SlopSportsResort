# ef_animcurve Rotate dual first range via RotRange table index 132->28 lines

- status: works
- tags: ef_animcurve,rotate,colouring,range-select
- scope: nw4r/ef/ef_animcurve AnimCurveExecuteRotate

symptom: Rotate dual-random branch: ra select 'add r6,r27,r4; addi r6,r6,4' vs target 'add r4,r27,r4; addi r6,r4,4' (temp and final pointer coalesced)
cause: U8Select 'pRanges + off + 4' evaluates into the result variable; target computes &tbl->datas[i] into a temp then +4 into the final var (same as GetRandomRangeStride/RotGetRandomRange select form)
fix: Keep F32Random hash, but select with RotRange* rangeA = &pRangeTbl->datas[cmdSeed0] / &pRandomTbl->datas[(r>>16)%count] + MixRandom; after 'u32 random0 = rangeRandom0;' add 'f32* ra = rangeA->v;' and test rangeA->sign. 99.068->99.167, 132->28 diff lines. Declaring ra right after the if/else instead -> back to 132.
