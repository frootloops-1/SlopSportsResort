# fn_801A2EFC loop-shape pass: btn recomputed per iteration, all shapes flat

- status: fails
- tags: fn-801a2efc,RPSysSystemWinMgr,loop
- source: claude 2026-10-26

symptom: target recomputes btn each iteration (clrlwi/mulli 0x1c/add) and ends addi/cmplwi 2; natural form gives P r28,i r30,c1 r27,btn r29 vs target P r27,i r29,c1 r30,btn r28
cause: pBtn++ walk changes code (addi stride, 472 lines); per-iteration Button* pBtn / Button& keeps code but btn colours r31 (468 lines); (pLayout,pBtn[,sel]) helpers flat 486; u32 i with (u8) index identical; int i gives cmpwi
fix: unsolved: only an extra invisible GPR node in the pAnm inner blocks gives the exact signature
