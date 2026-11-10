# RPSports_801fdbc0: unit with all-extern lbl_ rodata/data - define tables/vtable, descending source order

- status: works
- tags: data,rodata,vtable,order,sdata2,pool
- scope: RPSports_801fdbc0
- source: worker

symptom: .rodata/.data/.sdata 0% and .sdata2 66%, order_check mismatch; asm_diff on objdiff section 100 hides stack-slot diffs
cause: unit had no data definitions: strings read as lbl_80389028+off, tables/arrays/vtable extern; sdata2 named floats (-5000, -120, 0.5, 0) extern; functions emitted in REVERSE source order
fix: replace base+off with string literals (offsets land right, objdiff matches by offset); define SpPaneName[15]/const char*[N] arrays at the top (strings pool first), const u32 tables at END of file as extern const (no const-folding), vtable as void*[8]{0,0,fn...}, sdata ptr[2], 4th NULL in 3158 array; extern const f32 x4 at end; reorder_fn.py to DESCENDING address order (emission is reverse) + prototype block + move decl block up; dead static SpPoolSeed for N_scene_00; flip_gate then showed 6 bytes (one slot swap)
