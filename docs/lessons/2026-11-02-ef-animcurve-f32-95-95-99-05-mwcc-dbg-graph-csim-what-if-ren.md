# ef_animcurve F32 95.95 -> 99.05: mwcc_dbg graph + csim what-if renumbering found the source levers

- status: works
- tags: ef_animcurve,F32,regalloc,mwcc-debugger
- scope: nw4r/ef/ef_animcurve

symptom: F32 610 changed lines, colouring off from the count scan on (count r9, keySize r3, rangeSize r7 vs r10/r4/r3)
cause: rangeSize must be coloured before the GetRandomRangeStride @ temps (needs a late vreg), the dual first range index must be a named caller local (drops one pRandoms neighbour so the saved hierarchy holds), named order nextLoop>idx>loFrame and cmdSeed0>cmdSeed1>random0, and the count*4 temp must be created before the key-count load
fix: const u32& rangeSize = count*8 (R17, as in U8); forecast GetRandomRangeStrideIdx(by-value u32 rangeIdx) for both dual keys with u16 cmdSeed0/cmdSeed1 named; declare nextLoop, idx before loFrame; C89 decls with assignment order frame, keys, keySize, hi. Method: tools/mwcc_dbg.sh dump + a full colour simulator (sweep ascending K=29, lowest free reg, r0 only where dump had r0) reproduced all 500 nodes; what-if renumbering predicted each lever before compiling.
