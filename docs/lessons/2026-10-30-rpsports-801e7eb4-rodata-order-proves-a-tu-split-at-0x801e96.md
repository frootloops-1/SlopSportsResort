# RPSports_801E7EB4 rodata order proves a TU split at 0x801E9650 (Main controller)

- status: open
- tags: tu-split,rodata,stringBase0,splits,sbss,RPSports_801E7EB4
- scope: Pack/RPSports/RPSportsCommon/RPSports_801E7EB4
- source: worker 2026-10-31

symptom: target .rodata: PS tables (0x90,0x90,0x40), @stringBase0, then Main ptmf table (0xD8) + sMsgName after the string pool; ours puts Main table first; fn_801EA1C4 phantom R_PPC_NONE (table-4 lands in @stringBase0)
cause: @stringBase0 is always last in a TU's rodata, so data after it is another TU. Compiling the file as two halves (PS fns 0x801E7EB4..0x801E9650, Main fns 0x801E9650..0x801EA458) gives exactly the target rodata order for each half; Main uses no strings/sdata2 and owns sbss lbl_804BF710
fix: orchestrator: split text 0x801E9650, rodata 0x80387348, sbss 0x804BF710 to a new Main TU (maybe merged with RPSports_801ea458, which holds StateMachine<Main>); PS TU rodata start 0x80387008 or drop pad lbl_80387004; lbl_804BF710 size 0x4. PS TU must extern the singleton
