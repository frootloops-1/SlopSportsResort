# Defining a const f32 before use makes the compiler inline it; named consts land after the pool

- status: works
- tags: rpbox,sdata2,dedupe,extern-const
- scope: RPBox_802c7924
- source: x-golbox-1029

symptom: extern const f32 lbl = 1.0f defined at the top of the TU still produced literal pool entries and the named const was emitted after the pool; plain literals dedupe so the original's second 1.0f (4D18) disappears
cause: a visible const initializer is constant-folded; a definition after every use is opaque and is emitted after the pool (end of .sdata2)
fix: for a distinct trailing duplicate literal: extern decl at top, definition at the end of the file (R17 + ledger); first-use literals stay plain literals
