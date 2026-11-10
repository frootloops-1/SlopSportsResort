# RPSportsButtonA: lbl_ extern string pool + sdata/data = second TU; split at 0x801D0120

- status: works
- tags: split,rodata,stringBase0,sdata,data,RPSports
- scope: RPSportsButtonA,RPSports_801D0120
- source: claude/w-buttona-data-1029

symptom: unit_cmp rodata 35 data 35 sdata2 71; strings reached as lbl_80383ED0+off, SIZE-MISMATCH on lbl_ objects; ButtonA could not flip
cause: Two TUs in one range: functions use 0x80383ED0 as the pool base (second @stringBase0), a pool start that is not the unit's first string; text boundary has no data evidence
fix: split splits.txt at 0x801D0120 (+rodata 0x80383ED0, data/sdata/sdata2 to the second TU); ButtonA (2 fns, 112B pool) flips with DOL 0; second TU: literals + file-scope sdata pointers + hand vtable; one dead pool string (N_frameDown_00) pooled right after T_caption_01 (R17). sdata2 order still open
