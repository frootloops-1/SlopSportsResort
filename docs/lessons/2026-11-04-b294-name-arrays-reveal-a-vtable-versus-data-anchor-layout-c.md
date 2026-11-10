# b294 name arrays reveal a vtable versus data-anchor layout conflict

- status: works
- tags: RPSports_8020b294,anchor,vtable,TU-boundary
- scope: fn_8020B6DC
- source: codex-b6dc-1104

symptom: fn_8020B6DC reaches 99.3 but source data anchor begins at the manual vtable, 16 bytes before retail name-array base.
cause: Four file-static writable arrays reproduce retail redundant addi instructions and loop coloring; a manual vtable shares the anchor whereas a compiler vtable is excluded.
fix: Real virtual-class trial made B6DC instructions exact apart from relocation names, but emitted the vtable last and broke data order. Early codegen, explicit .data section, weak vtable and scoped pool_data off did not solve both. Retain verified manual layout; inspect TU boundaries/vtable ownership next.

resolution (2026-11-04): split the holder ctor/dtor at .text 0x8020B294-0x8020B340 and vtable .data 0x803C3518-0x803C3528 from the remainder starting at 0x8020B340 / 0x803C3528. B6DC body unchanged, 99.3 -> 100. Independent relocation of 16 source sites gives all 448 original DOL bytes at 0x8020B6DC; all data sections remain 100, no regressions.
