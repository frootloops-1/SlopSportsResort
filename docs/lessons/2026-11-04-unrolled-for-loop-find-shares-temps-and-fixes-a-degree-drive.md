# Unrolled for-loop find shares temps and fixes a degree-driven colour swap

- status: works
- tags: register,loop,unroll,interference
- scope: RPSportsCommon/RPSports_801f1d4c
- source: claude/sp801f1-1104c 46d1f8977

symptom: 3-way if-chain over array entries gives self/idx swapped regs (self r31 vs retail r30)
cause: Original was a fully unrolled for loop; shared compare-load vreg lowers self's interference degree 29->28
fix: for (s32 i=0;i<3;i++) if (id==e[i].id) return i; plus s32 idx with (u8) casts keeps both clrlwi
