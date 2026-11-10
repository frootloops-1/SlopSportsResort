# Inner-block pointer vs outer local r30/r31 swap: declare inner first

- status: works
- tags: mwcc,regalloc,locals
- scope: RPGol_802bca94
- source: opus-worker

symptom: fn_802BD320 work ptr and inner-else pointer swapped
cause: declaration order sets rank
fix: declare the inner pointer (GolVec3* a;) before the outer local
