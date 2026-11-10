# ef_animcurve Child: header-cast helper arg, shared C89 loop vars, pCmdList+= all fail

- status: fails
- tags: ef_animcurve,AnimCurveExecuteChild,regalloc
- scope: ef_animcurve
- source: ef_animcurve Child 2026-10-29

symptom: AnimCurveExecuteChild 97.88 pure register permutation (696 lines)
cause: Target colours pCmdList first (r31), then named pKeyTbl,pRandomTbl,pNameTbl,frame0,loop0,frame1,loop1, then pKeys r23, seed r22, pParticle r21. Under the exact allocator model pCmdList(r32) can never be pushed after pParticle(r33): identical remaining neighbourhoods and coalescing keeps the lower vreg, so pHeader cannot survive as a high named vreg. Decl-order perms of all 8 top-level named (40320, simulated) max 6/21 key nodes.
fix: Helper takes AnimCurveHeader* at both calls: 96.8. Shared top-level int i/pKey/loop (C89 style, no web splitting occurs): 97.5, 826 lines. pCmdList += sizeof(header) before pKeyTbl: identical 97.88 (optimizer renames). Park; graph needs a structural difference not visible in final asm.
