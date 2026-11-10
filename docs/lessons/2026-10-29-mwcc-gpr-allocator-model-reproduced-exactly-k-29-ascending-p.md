# MWCC GPR allocator model reproduced exactly (K=29 ascending passes, lowest-used-free else new-highest)

- status: works
- tags: mwcc,regalloc,mwcc_dbg,simulator,ef_animcurve
- scope: GC/3.0a5.2 C++
- source: ef_animcurve Child 2026-10-29

symptom: Need to predict colouring from a mwcc_dbg dump without recompiling
cause: Simplify = repeated ascending-vreg passes pushing nodes with current degree<29 (phys neighbours r0,r1,r3-r12 count). Select = pop; pick LOWEST already-used free reg (volatiles r0,r3-r12 pre-used), else the highest unused nonvolatile. Coalescing always keeps the LOWER vreg (pHeader r65 into pCmdList r32; pKeys into pKey2).
fix: Sim reproduced all 440 nodes of AnimCurveExecuteChild exactly. Use it for what-if renumbering before compiling. Script: scratchpad childw/scripts/col.py+whatif.py (copy to tools if wanted).
