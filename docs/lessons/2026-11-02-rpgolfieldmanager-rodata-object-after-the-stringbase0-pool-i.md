# RPGolFieldManager: rodata object after the @stringBase0 pool is impossible in-TU: it is the next TU's pool (split it out)

- status: works
- tags: rodata,stringBase0,split,tu-boundary,ibinary
- scope: RPGolFieldManager
- source: claude/golfield-data-1102

symptom: extern const char blob[0x48] defined at file end (also weak, section('.rodata'), template static member) always lands BEFORE @stringBase0 in .rodata, never after
cause: MWCC places the string pool after all explicit parse-time rodata; lbl_8038E458 (scene_ModelMisc path + IBinary asserts, duplicated pool tail) is another TU's pool
fix: splits.txt: move FM .rodata end to 0x8038E458 and .sdata end to 0x804BE828, give RPGolDrawManager .rodata 0x8038E458-4A0 + .sdata 0x804BE828-830, symbols @stringBase0 scope:local at E458; DrawManager.cpp defines const char* lbl_804BE828[2]={pmmisc path,0} plus a dead weak SetBinary copy (R17 ledger 77). DOL 0, both units 100 on those sections
