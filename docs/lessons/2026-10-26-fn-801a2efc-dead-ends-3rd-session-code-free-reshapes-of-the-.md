# fn_801A2EFC dead ends 3rd session: code-free reshapes of the pAnm[1] block

- status: fails
- tags: regalloc,winmgr,2EFC
- scope: Pack/RPKernel/RPSysSystemWinMgr
- source: claude

symptom: 98.5 natural restart()
cause: these forms are folded before RA, so the allocator sees the same graph
fix: no change: Button& at loop top (worse, btn r31), per-button inline helper with u8 i or Button* param, block-local Button&/Button*, ref to pPane/unk18, refs declared outside the innermost block, free getter helpers for end/start, s32 end local, (pMgr->mButton+i)/(&mButton[i])/(*(pAnm+1)) forms
