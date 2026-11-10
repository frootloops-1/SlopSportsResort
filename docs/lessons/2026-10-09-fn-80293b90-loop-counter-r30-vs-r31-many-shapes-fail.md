# fn_80293B90 loop counter r30 vs r31: many shapes fail

- status: fails
- tags: RPGolFieldManager,loop,regalloc

symptom: counter in r30, original r31 (99.1%)
cause: unknown
fix: failed: inline item accessors, loop in inline helper, literal GolPath, block-scoped locals, do-while, j/off order
