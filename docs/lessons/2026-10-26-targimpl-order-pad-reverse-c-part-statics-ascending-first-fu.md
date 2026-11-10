# targimpl order+pad: reverse C part, statics ascending first; function_align 16/4 gives .o text align 16

- status: works
- tags: emission-order,padding,mwcc,metrotrk
- source: claude/trk-pad-1026

symptom: Unit 100% in objdiff but order differs and 12 pad bytes missing; after reordering, jump-table-like rodata (@142/@149/@156 nop arrays) swapped
cause: C functions emit reverse of source; local static arrays in inlined statics are numbered by compile order; splits align:16 does not affect compiled .o, linker uses .o section align
fix: reverse non-static C fns; keep deferred statics defined ascending before them (preserves @ numbering); first stub in next unit gets #pragma function_align 16 then function_align 4 so .text align is 16 with size unchanged; trim gap symbol + split end
