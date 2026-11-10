# ef_animcurve Texture: pHeader copy colouring dead ends

- status: fails
- tags: ef_animcurve,regalloc
- scope: nw4r/ef/ef_animcurve
- source: claude/ac-*-1028

symptom: pHeader (copy of pCmdList) r24 ours vs r31 target, shifts all saved regs
cause: unknown; same pattern in Child (target r31)
fix: dead: pKeyTbl from pCmdList with pHeader after tables, pCmdList+=sizeof, TexHeader() getter, TexHash(pHeader,..) inline, tick by u32& in inline, whole-body inline 94.4, pHeader=(Hdr*)pKeyTbl-1 98.1, inline frame helper w/ count-before-n 99.2
