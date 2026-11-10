# Ternary 0/7 goes branchless; if-assign keeps branch

- status: works
- tags: mwcc,branchless
- scope: RPGol_802bb608
- source: opus-worker

symptom: s = on ? 0 : 7 gave neg/or/srawi/andc; orig branches
cause: MWCC branchless select for constant ternary
fix: s32 m=7; if(on) m=0;
