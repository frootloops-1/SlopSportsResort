# resort: symbols.txt vtable sizes may include 4 bytes of padding and block a flip

- status: works
- tags: resort,symbols,vtable,flip
- source: rp-graphics-layouts 2026-11-09

symptom: code 100% but .data SIZE-MISMATCH on the vtable
cause: dtk sized the vtable to the next symbol
fix: use the real size (ogws symbol: __vt__17RPGrpViewRender2D 0x2C, __vt__22RPGrpModelBoundingInfo 0xC); both units then flipped
