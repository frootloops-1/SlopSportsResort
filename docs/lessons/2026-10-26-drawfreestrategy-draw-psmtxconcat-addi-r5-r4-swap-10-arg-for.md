# DrawFreeStrategy::Draw PSMTXConcat addi r5/r4 swap: 10 arg-formation variants no gain

- status: fails
- tags: schedule,MTXConcat,addi,args,ef_drawfreestrategy
- scope: src/nw4r/ef/drawstrategy/ef_drawfreestrategy.cpp

symptom: Before bl PSMTXConcat target emits addi r5,r1,0x90 (posMtx) then addi r4,r1,0xc0 (glbMtx); ours emits r4 then r5 (same as matching point/line strategies)
cause: Unknown; block is just {mr r3,r26; addi r4; addi r5; bl} so IR arg order differs. Not caused by inline_depth pragma
fix: No fix. Tried: const MTX34* pView local, direct PSMTXConcat(*view,glb,pos), pPos/pGlb pointer locals, MTX34Mult return value into GXLoadPosMtxImm, swapped glb/pos declarations (offsets change, worse), px/py computation moved before/after CalcGlobalMtx or Mult (worse, 38 lines), pragma inline_depth removed. All leave 2-line diff or worse.
