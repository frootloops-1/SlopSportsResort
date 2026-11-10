# if/else storing one of two float constants needs a ternary

- status: works
- tags: ternary,float,branch
- scope: RPTns_8022e93c
- source: sonnet worker 2026-10-14

symptom: branch layout differs for x = c ? 0.25f : 0.2f written as if/else
cause: ternary assigned once yields orig layout
fix: write f = cond ? a : b; then single store (fn_8022EBA4)
