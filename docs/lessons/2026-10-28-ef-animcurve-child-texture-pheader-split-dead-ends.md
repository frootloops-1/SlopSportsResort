# ef_animcurve Child/Texture pHeader-split dead ends

- status: fails
- tags: ef_animcurve,regalloc
- scope: nw4r/ef/ef_animcurve
- source: claude/ac-hdr-1028

symptom: trying to split pHeader from param pCmdList
cause: copies coalesced or reassignments split off
fix: dead (byte-identical): pHeader declared first; pCmdList+=sizeof alone (folded); dead store pCmdList=pNameTbl; pCmdList=pRandomTbl+randomTable as pNameTbl; non-const params. Child: pKeyTbl->datas instead of named pKeys 93.0; CalcCurveFrameChild(AnimCurveHeader*) 96.8 (params drop in order but saves r16/r17)
