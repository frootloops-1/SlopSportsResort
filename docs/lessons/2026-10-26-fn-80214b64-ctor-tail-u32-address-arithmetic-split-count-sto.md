# fn_80214B64 ctor tail: u32 address arithmetic, split count stores around vptr, vt2 local all no gain

- status: fails
- tags: dead-end,ctor,regalloc
- scope: RPTns_80214480
- source: claude

symptom: li r4,6 + addi r0 hoisted above stw 0x44 (98.32%)
cause: unknown; same wall as fn_802597F4/fn_8032F2B8
fix: tried (u32)lbl+0x24 store, count local split around vptr store, void** vt2 = lbl+9 local: all still 6 diff lines. Source unchanged.
