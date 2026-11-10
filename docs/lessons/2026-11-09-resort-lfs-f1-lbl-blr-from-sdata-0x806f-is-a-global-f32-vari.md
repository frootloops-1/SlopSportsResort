# resort: lfs f1,lbl;blr from .sdata (0x806F...) is a global f32 variable, not a literal

- status: works
- tags: resort,sdata,float
- scope: resort
- source: jsk-wkb

symptom: constant getter reads a float from .sdata
cause: only .sdata2 (0x807...) holds pooled literals; .sdata floats are variables
fix: write return lbl; with an extern f32 global. Generating C for simple asm shapes (empty fns, getters/setters, tail and vtable calls) gave 245 exact across 61 files
