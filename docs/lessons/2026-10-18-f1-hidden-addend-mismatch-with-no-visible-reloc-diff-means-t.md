# F1 hidden: addend mismatch with no visible reloc diff means target rodata symbols must merge into the symbol the source defines

- status: works
- tags: F1,hidden,rodata
- scope: RPSports_8020b294,RPSports_802041d0,RPGolMapObjBall
- source: claude/nm-data

symptom: addi rX,rY,0x1e8 DIFF_ARG_MISMATCH; objdiff resolves target as lbl_8038AAE1+15, ours lbl_8038A908+488
cause: target split string symbols
fix: merge target rodata symbols into one string_table matching name and size of the defined/extern symbol (RPSports_8020b294/802041d0/RPGolMapObjBall/801ef064/801E51B4: 18 fns to 100)
