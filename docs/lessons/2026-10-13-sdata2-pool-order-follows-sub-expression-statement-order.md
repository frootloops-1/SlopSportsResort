# sdata2 pool order follows sub-expression statement order

- status: works
- tags: sdata2,literals,pool
- scope: RPGol_802bb608
- source: opus-worker

symptom: (s32)(100*(3.2808*(n/100))+5) pooled 5 before 3.2808
cause: pool is first-use order in emitted code
fix: split 3.2808*(n/100) into a separate statement so 3.2808 is pooled first
