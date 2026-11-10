# resort: RPSysKokeshiManager needs Resort layouts in 6 shared headers and a wider split

- status: open
- tags: resort,RPSysKokeshiManager,layout
- scope: resort
- source: RP batch 4 (2026-11-09)

symptom: 7/8 functions exact only with temporary edits to RPSysKokeshiLocation, RPSysResourceManager, RPGrpModel, RPGrpModelResManager, RPGrpTexture, RPGrpModelMaterial headers
cause: Resort rewrote the kokeshi pipeline; file spans ~0x80245B7C..past 0x8024673C in reverse source order
fix: patches in the side-session notes folder (kokeshi_unit.patch, kokeshi_shared_needs.patch); assign one worker owning those headers
