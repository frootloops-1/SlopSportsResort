# sdata2 pool order follows IR creation, not text order

- status: works
- tags: sdata2,pool,order,literal
- scope: RPGol_802c16a4
- source: claude/rpgolscene-unsplit

symptom: two literals pooled in the wrong order though code matches
cause: inline-call args evaluate right to left and calls linearize first
fix: an unused local (f32 k = 30.0f;) earlier in the fn creates the pool entry first with no codegen change
