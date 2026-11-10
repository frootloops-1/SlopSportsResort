# Address-taken locals get stack slots in reverse declaration order

- status: works
- tags: stack,locals

symptom: swapped addi r4/r5 for two byte flags passed by address
cause: first-declared local lands at the higher sp offset
fix: swap declaration order (fn_801E218C)
