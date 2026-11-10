# fn_801A2EFC third pass: const-1 use before restart reset temps gives exact regs but moves a store; extra node after start() works

- status: fails
- tags: regalloc,winmgr,2EFC,const1
- scope: Pack/RPKernel/RPSysSystemWinMgr

symptom: 99.5 workaround vs 98.5 natural
cause: const1 rank fixed by early use in pAnm[1] block; ~75 variants
fix: unsolved: park at 99.5 (split reset/start); a permuter scored on register signature or different restart() header body untested
