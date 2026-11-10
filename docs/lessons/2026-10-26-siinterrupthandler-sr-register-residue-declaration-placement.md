# SIInterruptHandler sr register residue: declaration placement and permuter gave nothing

- status: fails
- tags: SIBios,register,permuter,sr
- scope: revolution/SI/SIBios
- source: SIBios session 3

symptom: After volatile, only diff is sr in r18 (target r26) shifting x/i/ptrs/first-block regs by one
cause: Unknown priority difference for sr; sr hoisted to block top/function scope/with enabled, sr += in place, x before vcount, 6 min permuter (-j6): no gain or worse
fix: parked; try only a new structural idea
