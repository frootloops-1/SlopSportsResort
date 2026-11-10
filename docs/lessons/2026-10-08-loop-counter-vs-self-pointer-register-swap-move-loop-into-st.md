# Loop counter vs self-pointer register swap: move loop into static inline helper

- status: works
- tags: mwcc,regalloc,loop

symptom: r30/r31 swap between loop index and strength-reduced self pointer
cause: allocation order differs when the loop is in the caller
fix: static inline UpdateAll(self) helper holding the whole loop
