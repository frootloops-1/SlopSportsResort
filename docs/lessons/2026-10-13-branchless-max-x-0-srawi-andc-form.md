# Branchless max(x,0) srawi/andc form

- status: works
- tags: mwcc,branchless,clamp
- scope: RPGol_802bb608
- source: sonnet-worker

symptom: x<0?0:x compiled to a branch; orig srawi+andc
cause: original source used bit trick
fix: x = x & ~(x >> 31)
