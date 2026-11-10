# static float init from extern const: real sinit, rename fn_ to __sinit_Unit_cpp scope:local

- status: works
- tags: ctors,sinit,sbss
- scope: RPGolFieldManager
- source: claude/golfield-data-1102

symptom: .ctors section 0 with a hand-written fn_XXXX that copies one extern const f32 into an sbss f32
cause: f32 g = lbl_const; with lbl_const only declared extern is a dynamic initialiser; MWCC emits __sinit_File_cpp and the .ctors entry
fix: delete hand fn, write f32 lbl_804BF86C = lbl_804C3F6C; (const defined later in file); symbols.txt rename fn_80294178 -> __sinit_ backslash RPGolFieldManager_cpp scope:local. .ctors 100, sinit 100
