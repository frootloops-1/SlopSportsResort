# Check local TYPES vs getter return types: s32 local from int getter gets top rank (long conversion temp)

- status: works
- tags: regalloc,s32,int,types,coloring
- scope: Pack/RPKernel/RPSysControllerMgr

symptom: sceneReset 98.2: blamed j*4, really fromChan
cause: s32 (long) local initialised from int getter ranks first (colored before strength-reduced index regs)
fix: declare as int matching the getter return type; diagnostic: delete/merge a suspected local and watch other registers
