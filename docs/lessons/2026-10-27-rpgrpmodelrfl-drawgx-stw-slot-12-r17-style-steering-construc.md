# RPGrpModelRfl::DrawGX stw slot: 12 R17-style steering constructs (identical-arm ternary, local ptr, ptr-to-ptr, u32 cast, dead load, duplicate store, table ptr) none move the stw

- status: fails
- tags: RPGrpModelRfl,DrawGX,stw,R17,marker,scheduling
- scope: Pack/RPGraphics/RPGrpModelRfl DrawGX 0x801B5178

symptom: retail lwz,li,lis,stw,lbzx,addi,stb; ours lwz,li,lis,lbzx,addi,stw,stb
cause: Probe with real RPGrpModelRfl types: same-value ternary, RPGrpModel* local, RPGrpModel** indirection, (RPGrpModel*)(u32) cast, static_cast, dead lhz before the store, duplicate trailing store, u8* to tevStageNum, const u8* table pointer all keep the stw after addi; storing before the type load puts stw first; a ternary on the table index changes the code. Ghidra: only callers are DrawProc (0x801B5A84, r3=object, r7=colour ptr, r8=opa, r9=0) and the recursive mpRflParent call (r9=1); no vtable/data refs, so member vs static is not distinguishable.
fix: open: no marker found. Next levers: permuter on the 4-store block (pure scheduling residue), or leave NonMatching.
