# WPAD data_type parsers: u32 loop counter + no _devCmpt block close the family

- status: works
- tags: WPAD,loop,unroll,join-moved
- scope: revolution/WPAD/WPADHIDParser
- source: claude/nm-4 2026-10-16 sonnet batch 2-3

symptom: __a1_32/35/37/3e/3f_data_type ~85% join-moved
cause: int clear-loop counter gives pointer-bump loop instead of unrolled stbx/ctr; extra if(_devCmpt[chan]) classic-stick-zero block the original lacks
fix: u32 i; delete the _devCmpt block; rxBufs[idx] not rxBufs+idx*SIZE. 32/35/37 -> 100, 3e/3f -> 99.9 (PI constant reloc only)
