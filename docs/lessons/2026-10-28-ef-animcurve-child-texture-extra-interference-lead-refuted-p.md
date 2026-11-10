# ef_animcurve Child/Texture: extra-interference lead refuted; pHeader merged into param node

- status: open
- tags: ef_animcurve,regalloc,coalesce
- scope: nw4r/ef/ef_animcurve
- source: claude/ac-hdr-1028

symptom: pCmdList/pHeader copy coloured last (ours) vs first r31 (target)
cause: pHeader and param pCmdList coalesce into one node with the param's (oldest) vreg; saved GPR counts and long-lived values match target (Child r18-r31, Texture r23-r31)
fix: proof: walking pCmdList through the tables (pHeader=(Hdr*)pCmdList; pCmdList+=sizeof; pKeyTbl=pCmdList; pCmdList+=keyTable;...) gives target pHeader r31 + tables r30-r28 but adds 3 mr (Texture 96.5). Missing: a code-free construct that keeps pHeader a separate node
