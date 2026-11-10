# resort: asm diff of only bl fn_XXXX vs bl __ct__ is a missing symbol rename

- status: works
- tags: resort,bowling,data,flip

symptom: 99.x function with identical asm
cause: callee unnamed in symbols.txt
fix: rename: 0x801C052C __ct__Q23EGG8Vector3fFfff, 0x8020B108 nw4r MTX34 copy ctor
