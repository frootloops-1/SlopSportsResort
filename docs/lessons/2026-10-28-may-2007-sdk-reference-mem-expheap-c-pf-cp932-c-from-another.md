# May-2007 SDK reference (mem_expHeap.c, pf_cp932.c) from another decomp: no codegen gain on our Nov-2006 MWCC

- status: fails
- tags: mem_expHeap,RecycleRegion_,pf_cp932,reference,sdk-version
- source: user-provided files 2026-10-28; experiment worktree /private/tmp/ogws-cp932-1028

symptom: RecycleRegion_ r5/r6 load-order swap (99.90%); cp932 OEM2Unicode/Unicode2OEM r3/r5 + li r3,1 scheduling (98.53%)
cause: Reference spellings compile to the same bytes here: typed MemRegion struct + const MemRegion* param + struct-copy init for RecycleRegion_; 'cp932_lead + 0xFEC0' and the extra 'u16 temp' (reference comment: not in DWARF) for cp932; table moved from pf_cp932.h into the .c also unchanged (rodata 17016 vs 17010 is split-end alignment padding, not content; table data identical to ours). Our function bodies already equal the reference line for line.
fix: Nothing to import; do not retry these spellings. Reference is useful only as a structure cross-check (MemRegion helpers, dead-stripped inline MEMResizeForMBlockExpHeap/MEMAdjustExpHeap/GetAllocatableSize inlines).
