# RPSysLayout: inline-helper locals get lower stack slots; hoisted name+FindID pointer; merge 1-byte sdata2 symbols

- status: works
- tags: layout,stack-slot,static-inline,sdata2,symbols
- scope: Pack/RPKernel/RPSysLayout

symptom: calc VEC2 slots swapped; changeFontColor GPR priority; drawKokeshiIcon reloc-only 99.1
cause: locals in static inline get lower stack addresses; 4-byte GXColor split into four 1-byte symbols
fix: move local into static inline helper; one-expression (f32)a/(f32)b; compare+bool in static inline bool; merge lbl_804C15F4-7 into one size-4 symbol in symbols.txt
