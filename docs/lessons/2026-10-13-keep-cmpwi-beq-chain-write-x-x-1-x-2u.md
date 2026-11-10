# Keep cmpwi/beq chain: write !x || x==1 (|| x==2u)

- status: works
- tags: mwcc,branches,compare
- scope: RPGol_802bca94
- source: opus-worker

symptom: x==0||x==1 merged to cmplwi x,1; x==1||x==2 to subi/cmplwi
cause: MWCC range merge
fix: !x || x==1 (|| x==2u); static inline/const-left/switch did not help
