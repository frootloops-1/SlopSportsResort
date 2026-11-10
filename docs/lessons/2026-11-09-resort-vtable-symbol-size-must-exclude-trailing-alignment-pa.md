# resort: vtable symbol size must exclude trailing alignment padding

- status: works
- tags: resort,vtable,symbols,data
- scope: resort
- source: rp9b-renderer

symptom: unit_cmp SIZE-MISMATCH on __vt__18IRPGrpRendererProc, .data 96.66%
cause: symbols.txt size 0x18 included 4 bytes of padding before the next unit's .data; emitted vtable is 0x14
fix: set the symbols.txt size to the real vtable size (5 words = 0x14)
