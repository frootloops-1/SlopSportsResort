# Tail-call pair needs condition order if (idx >= 3) A else B

- status: works
- tags: mwcc,tailcall,branch

symptom: blt layout differs
cause: if/else ordering
fix: write the >= condition first
