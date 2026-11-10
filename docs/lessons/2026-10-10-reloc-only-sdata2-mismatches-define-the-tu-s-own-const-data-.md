# Reloc-only .sdata2 mismatches: define the TU's own const data before the pool

- status: works
- tags: sdata2,data,layout,reloc
- scope: RPGolDrawManager

symptom: 13 sda21 consts at wrong offsets; extern const lbl_ color/bytes owned by this TU
cause: object's .sdata2 begins with global const data (GXColor + u8 table referenced by sibling TUs) that we declared extern
fix: define extern const GolCol lbl_X = {...}; extern const u8 lbl_Y = n; in source; make extern float labels literals; also define .data vtable and .sbss global
