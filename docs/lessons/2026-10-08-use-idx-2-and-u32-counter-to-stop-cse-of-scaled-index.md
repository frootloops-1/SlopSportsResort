# Use idx<<2 and u32 counter to stop CSE of scaled index

- status: works
- tags: mwcc,cse,index

symptom: scaled index reused across loops/branches (extra saved reg)
cause: idx*4 CSE with names[idx] indexing
fix: write idx << 2; u32 counter in the later unrolled loop
