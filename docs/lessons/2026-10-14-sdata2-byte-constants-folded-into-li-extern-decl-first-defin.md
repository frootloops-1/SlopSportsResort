# sdata2 byte constants folded into li: extern decl first, define at file end

- status: works
- tags: sdata2,const
- scope: RPGol_802adb7c
- source: fn_802AE07C

symptom: li instead of lbz sym@sda21
cause: initializer visible before use
fix: extern const u8 lbl_X; before users; define in extern C block at end of file
