# fn_80354914 li r0,0 late: pre-RA scheduler ~100-IR-node regions; unrolled inlined 12-iter mtx copy loop moves the region boundary (real layout from sibling unit)

- status: works
- tags: rpbow,80354914,scheduler,region,unroll,struct-layout
- source: worker gol-p4914 2026-10-31

symptom: 98.5%: 2-line diff, li r0,0 ~15 copies late; 58 explicit float copies
cause: MWCC splits a block into ~100 IR node regions; a no-input li goes in the first free slot of its region. Retail's first region held extra nodes from a fully unrolled inlined 12-iteration matrix copy (fn_80326A64 shape) that emit nothing after unrolling
fix: rebuild typed sub-structs from sibling RPBow_80323790 fn_80326970/fn_80327054 (RecordB u32+7f at 0x00, two 12-float mtx at 0x20/0x50, vec 0x80, float 0x8C, vec 0x90, 6 vecs 0x9C, float 0xE4); copy mtx via for(i<12) helper, RecordB member by member (whole-struct assignment moves record ptr r5->r6), vecs by struct assignment. Diagnostic: delete copies one at a time; fixed absolute offset of the stray insn = region boundary. Permuter (9 min) useless for region walls.
