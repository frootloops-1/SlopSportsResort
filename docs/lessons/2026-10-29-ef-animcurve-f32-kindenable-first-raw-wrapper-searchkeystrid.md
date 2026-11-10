# ef_animcurve F32 kindEnable-first, Raw wrapper, SearchKeyStride, flag args, mask split all regress

- status: fails
- tags: ef_animcurve,F32,regalloc

symptom: F32 95.62 register colouring wall
cause: Each change moves the wrong vreg: kindEnable-first gives kindEnable r26 under flags r27; CalcCurveFrameFRaw only swaps n/flags vregs; flags-free CalcCurveFrameF (shared) keeps CSE flags at r27 and costs Rotate
fix: kindEnable before pKeys 95.5; no-flags-local helper 95.5 (+Rotate 99.07->99.0); CalcCurveFrameFRaw 95.6 (lower); Raw+kindEnable-first 95.5; SearchKeyStride for search 95.3; named flag0/flag1/flag as GetRandomRangeStride arg 94.5; scanMask/mask split 94.8. All reverted
