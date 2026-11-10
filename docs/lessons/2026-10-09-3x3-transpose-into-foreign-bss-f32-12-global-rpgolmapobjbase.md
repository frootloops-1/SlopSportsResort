# 3x3 transpose into foreign .bss f32[12] global (RPGolMapObjBase)

- status: works
- tags: golf,bss,extern,transpose,RPGolMapObjBase
- scope: RPGolMapObjBase
- source: sonnet

symptom: fn_80290390 writes transposed matrix into lbl_804A8900 with zeros from sdata2
cause: global owned by another object
fix: extern f32 lbl_804A8900[12] in extern C; local f32 m[12] with m[9..11]=0.0f; element stores
