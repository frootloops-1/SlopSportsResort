# near-miss dead ends batch nm-4/1: frameless dead VEC2, TRK rodata struct, struct copy addi base

- status: fails
- tags: dead-store,rodata,struct-copy,REGALLOC
- source: claude/nm-4 2026-10-16 sonnet batch 1

symptom: fn_801E5234, InitMetroTRKCommTable, fn_801FB91C struct copy, fn_802131C8 wcscat order
cause: unused stack copy eliminated once frameless; shared rodata layout; MWCC folds struct-copy loads
fix: fn_801E5234 else{soundReady=1} right shape but drops VEC2 copy (78%); InitMetroTRKCommTable one 0x108 rodata struct with strs ptr -> 97.0 but TRK_board_display 100->99.2, reverted; SpW3 tmp=*src / array index do not give addi r5,r31,off copy; fn_802131C8 wcscat arg-eval order unresolved; DrawFreeStrategy::Draw reload is in ef_particle.h Draw_GetSizeY (header)
