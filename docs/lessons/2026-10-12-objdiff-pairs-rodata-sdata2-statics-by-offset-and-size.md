# objdiff pairs rodata/sdata2 statics by offset and size

- status: works
- tags: objdiff,rodata,sdata2,table,size
- scope: RPGrpModelAnmImplement
- source: sonnet worker, verified 2026-10-12

symptom: Functions using a const table stay at 99.7% though instructions look equal
cause: Table with wrong element count (TO_G3D_TYPE[Anm_Max]=32 vs orig 24, FROM_G3D_POLICY 20 vs 24) shifts data pairing
fix: Fix the array size/entry count to the original symbol size
