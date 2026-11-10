# Unfolded flag stores / flags reload: use EGG::TBitFlag<u32> reset()/set()

- status: works
- tags: mwcc,flags,tbitflag,RPSysTutorialWinMgr
- scope: RPSysTutorialWinMgr

symptom: li r0,0; ori r0,r0,imm unfolded, or lwz reload of a field already in a register
cause: original used inlined TBitFlag methods; local copies/casts/volatile do not reproduce it
fix: make the field EGG::TBitFlag<u32> and call reset(a); set(b); separate 'if(!a) return; if(!b) return;' gives single beq
