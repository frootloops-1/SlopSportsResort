# jump table before manual vtable in .data

- status: works
- tags: data-order,jumptable,vtable,rpbsb
- source: RPBsb_8028c450 2026-10-16

symptom: jumptable lands after vtable array in .data
cause: deferred codegen emits functions (and their jump tables) after file-scope data
fix: #pragma defer_codegen off, functions in ascending order, vtable array defined at end of file
