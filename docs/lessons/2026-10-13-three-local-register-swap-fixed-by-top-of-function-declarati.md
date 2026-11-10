# Three-local register swap fixed by top-of-function declaration order

- status: works
- tags: mwcc,regalloc,locals
- scope: RPGol_802bf4f8
- source: opus-worker

symptom: fn_802BF510 u8 saved / bool plural / msgId registers rotated
cause: declaration order sets relative rank
fix: declare at top in order msgId, saved, plural (brute-forced all 6)
