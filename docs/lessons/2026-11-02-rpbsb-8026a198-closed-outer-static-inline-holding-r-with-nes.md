# RPBsb_8026a198 closed: outer static inline holding r with nested inline lerp; data defs recipe (vtables void* arrays, non-const sdata, defer_codegen split, drop TU-end gap_ sbss)

- status: works
- tags: inline-nesting,fpr,colouring,sdata,sdata2,sbss,gap-symbol,RPBsb_8026a198
- scope: RPBsb_8026a198 fn_8026AA3C

symptom: fn_8026AA3C 99.8%: FPR swap r/frac with inline BsbTblLerp; unit data sections 0-46%
cause: Nested-expansion locals colour after outer-expansion locals, so r as a local of an outer inline gets its register before the inner frac. .sbss was 80% because of a TU-end dtk gap_ symbol (gap_11_804BF7F5_sbss, 3 bytes after an s8).
fix: Wrap rand-range + multiplier switch + judge.f00 = r*mul in an OUTER static inline void BsbSetJudgeF00(BsbCtlV*, f32 p) (name inferred) with BsbTblLerp(3,p) nested: 99.8 -> 100. Dead: r as inline param of a wrapper (BsbScaleR), BsbRandRange for r. Data: vtables as void* arrays at file end in address order with zero words where retail has no reloc; .sdata names are non-const f32 globals (change earlier 'extern const f32' to 'extern f32', else error 10563); split .sdata2 around the compiler u32->f32 double (@1343 at 0x40) with #pragma defer_codegen off plus an .sbss definition as the flush trigger; delete the end-of-unit gap_N_*_sbss line from symbols.txt (dtk does not regenerate it) to take .sbss to 100.
