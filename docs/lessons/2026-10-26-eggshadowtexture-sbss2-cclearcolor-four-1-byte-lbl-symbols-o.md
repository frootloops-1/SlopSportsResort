# eggShadowTexture sbss2 cClearColor: four 1-byte lbl_ symbols -> one 4-byte local

- status: works
- tags: symbols,sbss2,data
- scope: egg/gfxe/eggShadowTexture
- source: shadow-1026

symptom: .sbss2 0% (cClearColor bytes accessed via lbz +0..+3 split into 4 symbols)
cause: dtk split the GXColor const into per-byte lbl_ symbols, last one size 5 covering pad
fix: one symbol cClearColor__Q23EGG30@unnamed@eggShadowTexture_cpp@ size:0x4 scope:local; resplit; .sbss2 100, DOL 0 diff
