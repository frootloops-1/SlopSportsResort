# RPTns fn_80214B64: vt local, array-index stores, chained count assign, typed struct view, vt2-first all no gain

- status: fails
- tags: rptns,fn_80214B64,scheduler,r0

symptom: li r4,6 / addi r0,r3,0x24 hoisted above stw 0x44 (6 diff lines, 98.3%)
cause: scheduler hoists &lbl_803C37B0[9] add above second count store; none of the source spellings changes it
fix: Tried void** vt local + vt+9, s32*/void** index stores, chained *(0x44)=*(0x40)=6, struct view with vt/vt2/cap/cnt fields (same 6 lines), vt2-before-vt order (8 lines, worse). Source unchanged; parked.
