# sdata2 float one ulp below literal (0x40FAE147 vs 7.84f): write as a folded product

- status: works
- tags: sdata2,float
- scope: RPGol_802adb7c
- source: fn_802ADBA0

symptom: pool value differs by 1 ulp
cause: original computed constant
fix: 2.8f * 2.8f
