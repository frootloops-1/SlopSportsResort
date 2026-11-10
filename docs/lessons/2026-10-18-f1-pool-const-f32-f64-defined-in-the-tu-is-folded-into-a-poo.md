# F1 pool: const f32/f64 defined in the TU is folded into a pooled @N; delete the definition and rename the target lbl_ to @N

- status: works
- tags: F1,symbols,sdata2,itof
- scope: RPUtlMath,RPUtl_801C67B8,RPUtlLytFrameCursor
- source: claude/nm-data

symptom: pool/hidden+pool diff, target lbl_804Cxxxx vs our @N; includes 2^52 itof doubles
cause: compiler folds a defined const into the pool so objdiff never sees the lbl_ name
fix: remove 'extern const f32 lbl_X = v;' definition, use the literal, rename target lbl_ to our @N (scope:local); RPUtlMath 4 fns, RPUtl_801C67B8 4 fns, RPUtlLytFrameCursor
