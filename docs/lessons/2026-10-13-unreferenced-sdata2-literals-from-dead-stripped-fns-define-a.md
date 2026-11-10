# Unreferenced sdata2 literals from dead-stripped fns: define as extern const

- status: works
- tags: sdata2,deadstrip,literal,data
- scope: RPGol_802c7660
- source: claude/rpgolscene-unsplit

symptom: TU .sdata2 has floats (1,-1,0) no surviving code loads; object .sdata2 short
cause: functions using them were dead-stripped at link but their pool stayed
fix: extern "C" { extern const float lbl_X = 1.0f; ... } in address order (plain const at namespace scope has internal linkage and is dropped); DOL hash OK, trailing 4-byte pad absorbed
