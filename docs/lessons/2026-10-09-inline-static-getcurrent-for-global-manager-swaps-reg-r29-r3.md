# Inline static GetCurrent() for global manager swaps reg r29->r30

- status: works
- tags: RPGolFieldManager,inline,regalloc

symptom: global manager read lands in wrong callee-saved reg
cause: CW
fix: read through inline static accessor
