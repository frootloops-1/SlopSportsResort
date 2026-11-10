# Function-local/file-static arrays share one base register

- status: works
- tags: data,tables,regalloc,static
- scope: Pack/RPSports/RPSportsCommon/RPSysNunchukCheckScene/fn_801E2C8C

symptom: orig loads table base once (lis/addi r26) and uses addi base+0x70 + lwzx; a global struct gave per-loop lis/addi and lwz disp(rX) (75%)
cause: separate internal-linkage arrays are addressed off the .data section symbol, so MWCC CSEs one base; a global struct/array is addressed per symbol
fix: split the 0xD0 table into 5 static arrays (panes[4][7], anms[8], colors[4][2], names[4], oks[4]); split symbols.txt lbl_803C2150 into lbl_803C2150/21C0/21E0/2200/2210 scope:local so objdiff R_PPC_NONE pseudo-relocs match (99.4 -> 100)
