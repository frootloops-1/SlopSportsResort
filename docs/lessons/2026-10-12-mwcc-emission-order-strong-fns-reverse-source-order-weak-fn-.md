# MWCC emission order: strong fns reverse source order; weak fn goes after its source-last referencer; vptr after data needs a plain data base struct

- status: works
- tags: mwcc,layout,vtable,weak,emission,RPGrpModelRecord
- scope: Pack/RPGraphics/RPGrpModelRecord
- source: 2026-10-12 Claude RPGrpModelRecord

symptom: Object 12/12 fns exact but DOL differs: weak dtors/ctor at wrong .text position; vptr at 0x44 not 0
cause: MWCC emits out-of-line functions in reverse source order; a weak/inline fn is emitted right after the last-in-source function referencing it; vtables of out-of-line-key classes follow source order; MWCC puts the vptr at offset 0 unless the class derives from a non-polymorphic data base (then after it)
fix: Put fields in a plain base struct (class : Data); define dtors out of line in desired source slots; to pin a 4-byte weak ctor (EGG::Matrix34f) give a subclass an out-of-line ctor defined at that slot; #pragma dont_inline on around a ctor to stop it being inlined; 'int n = frames' local flipped store scheduling in a ctor
