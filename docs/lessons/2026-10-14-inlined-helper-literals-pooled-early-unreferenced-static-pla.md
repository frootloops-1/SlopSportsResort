# Inlined helper literals pooled early: unreferenced static placeholder fn calling the inline

- status: works
- tags: sdata2,pool-order
- scope: RPGol_802adb7c
- source: fn_802AE444

symptom: helper literals sit between other fns' literals
cause: dead-stripped fn created them
fix: static inline helper + unreferenced static fn calling it placed where the pool needs it; linker strips it (DOL OK)
