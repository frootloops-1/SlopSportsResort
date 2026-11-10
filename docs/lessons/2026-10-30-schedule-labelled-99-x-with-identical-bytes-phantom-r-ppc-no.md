# SCHEDULE-labelled 99.x with identical bytes: phantom R_PPC_NONE on subi from undefined extern table

- status: works
- tags: objdiff,R_PPC_NONE,rodata,phantom,schedule
- scope: Pack/RPSports/RPSportsCommon/RPSysLytMenuFrame

symptom: fn_801D84CC 99.39%, asm_diff identical, 1 instr DIFF_REPLACE on 'subi r4,r4,4' (struct-copy loop base) with no visible operand diff
cause: objdiff synthesizes R_PPC_NONE on target subi (sym-4 falls in preceding local @N); ours referenced the table as an undefined extern so no reloc could be synthesized
fix: define the extern const table (lbl_80384AF8) in the TU at END of file so it lands after the @N local-init rodata objects; defining it before the function put it at .rodata offset 0 and regressed a neighbour. Check objdiff JSON diff_kind per instruction before treating as scheduling
