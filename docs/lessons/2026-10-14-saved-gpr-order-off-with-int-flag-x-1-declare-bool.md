# Saved GPR order off with int flag = (x == 1): declare bool

- status: works
- tags: regalloc,bool
- scope: RPGol_802b1a0c
- source: fn_802B1AA4

symptom: r25 used instead of r26..r31
cause: int-typed compare result
fix: bool wide = sTVMode == 1;
