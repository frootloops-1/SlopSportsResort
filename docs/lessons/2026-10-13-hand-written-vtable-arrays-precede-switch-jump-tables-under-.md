# Hand-written vtable arrays precede switch jump tables under deferred codegen

- status: works
- tags: vtable,jumptable,data,defer_codegen,order
- scope: RPGol_802c16a4
- source: claude/rpgolscene-unsplit

symptom: .data: our void* vtable arrays land before the compiler jump tables; orig has jump tables first
cause: deferred codegen emits jump tables at function codegen time, after explicit data
fix: #pragma defer_codegen off at file top + write functions in ascending address order (emission = source order); define the arrays at file end. Real C++ classes with virtuals may also work under deferred mode (untested)
