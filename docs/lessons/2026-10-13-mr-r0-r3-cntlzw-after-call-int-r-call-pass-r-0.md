# mr r0,r3; cntlzw after call = int r = call(); pass r == 0

- status: works
- tags: mwcc,bool,call
- scope: RPGol_802bb608
- source: opus-worker

symptom: passing call()==0 inline gives plain cntlzw
cause: result held in a local first
fix: int r = call(); f(r == 0)
