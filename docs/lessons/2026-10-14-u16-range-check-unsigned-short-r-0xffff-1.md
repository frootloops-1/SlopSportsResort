# u16 range check: (unsigned short)(r + 0xFFFF) <= 1

- status: works
- tags: u16,compare
- scope: RPGolScene
- source: claude/rpgol-family

symptom: addis r4,r3,1; subi r0,r4,1 then clrlwi. not reproduced by (u16)(r-1)
cause: MWCC lowers +0xFFFF as addis/subi
fix: int r = fn(); (unsigned short)(r + 0xFFFF) <= 1; cmplwi on mode arg means unsigned
