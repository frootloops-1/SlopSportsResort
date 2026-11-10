# ef_animcurve U8/Rotate/F32 opcode-order diffs are colouring side effects

- status: open
- tags: ef_animcurve,schedule,regalloc
- scope: nw4r/ef/ef_animcurve
- source: claude/ac-*-1028

symptom: regalloc_diag says NOT-REGALLOC (neg/or/srwi. vs add+lbz, addis vs mulli order)
cause: target reuses registers (k1 in k0's r6, rnd in place), which constrains the schedule
fix: fix colouring, not statement shape. Dual-hash add order loop*C4+(S+H) comes from GetRandomRangeStride form, but using it moves pRanges to r31 (F32 95.1, Rotate flat 97.4). Dead: U8 7 key-setup orders 97.5-97.9, count*2 96.8, mask-loop inline (coalesced), F32 found-before-mid 94.2, kindEnable after loop 95.3, processFlag re-read (identical), frame calc pasted 95.5
