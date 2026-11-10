# DrawFreeStrategy::Draw addi r5/r4 swap: inline_depth pragma and more call shapes do not move it

- status: fails
- tags: ef_drawfreestrategy,PSMTXConcat,scheduling
- scope: nw4r/ef/drawstrategy/ef_drawfreestrategy

symptom: Only diff left in ef_drawfreestrategy: orig addi r5(pos,0x90) before addi r4(glb,0xc0); ours r4 then r5 (same as matching DrawLineStrategy)
cause: Unknown; theory: orig IR order is inline param order (pOut,pA,pB) or glb address CSE'd across CalcGlobalMtx call and rematerialised after r5. Line strategy has identical source and matches, so the difference is elsewhere in free's Draw
fix: No fix. Also tried: removing/changing #pragma inline_depth(1) (2,3), raw PSMTXConcat(*view,glb,pos), const MTX34& view local, pGlb/pPos pointer locals incl. CalcGlobalMtx(pGlb), moving px/py before the call (worse, 38 lines). All stay at 2 differing lines
