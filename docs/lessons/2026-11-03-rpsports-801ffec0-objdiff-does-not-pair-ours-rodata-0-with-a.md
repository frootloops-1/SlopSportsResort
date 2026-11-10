# RPSports_801ffec0: objdiff does not pair ours ...rodata.0 with a target @N symbol; rename the target @N to a local lbl

- status: works
- tags: rodata.0,anchor,symbols,objdiff,RPSports_801ffec0
- scope: Pack/RPSports
- source: claude/sp801ff-1103

symptom: fn_80200D38 lis/addi ...rodata.0 vs @2088 still a diff after adding the ...rodata.0 label to symbols.txt
cause: dtk keeps the object symbol for relocations; objdiff compares @N names specially and never pairs them with ...rodata.0
fix: symbols.txt: put '...rodata.0 = .rodata:<addr>; // type:label scope:local' BEFORE the first object and rename that @N object to lbl_<addr> scope:local; anchor rows vanish
