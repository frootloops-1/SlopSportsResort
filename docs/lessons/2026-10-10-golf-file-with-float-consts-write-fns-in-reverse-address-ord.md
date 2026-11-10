# Golf file with float consts: write fns in reverse address order (sdata2 pool order)

- status: works
- tags: rpgolmath,sdata2,pool-order,function-order
- scope: RPGolMath
- source: sonnet

symptom: forward-ordered file gives 99.6% on every constant-using fn
cause: .sdata2 pool is emitted reversed relative to function order
fix: write the source file in reverse address order
