# Zero word gap between anonymous init object and float pool

- status: works
- tags: sdata2
- scope: RPGol_802aaf88
- source: RPGol_802aaf88

symptom: 4-byte zero gap in .sdata2
cause: named global emitted after parse-time anon objects
fix: extern const u32 lbl_X = 0; (unreferenced)
