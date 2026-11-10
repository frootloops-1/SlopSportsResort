# fn_801DF770 / RPSysLytPlayerSelect: 98.89 is a phantom R_PPC_NONE from rodata layout, not code

- status: open
- tags: RPSysLytPlayerSelect,fn_801DF770,rodata,objdiff
- scope: Pack/RPSports/RPSportsCommon/RPSysLytPlayerSelect

symptom: SCHEDULE-pure 1 wrong, asm_diff identical
cause: objdiff synthesizes R_PPC_NONE on subi r4,r4,4 before copy loop; array-4 lands in lbl_803857F8 in target but padding in ours; unit .rodata 12.6%
fix: unit-wide rodata rebuild: define lbl_80385718, @29272, @29388, lbl_803857F8 ahead of @28083; maybe rename lbl_80385B28 to @stringBase0 in symbols.txt
