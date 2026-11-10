# Two {-1} pool words per function = two one-word aggregates; asm with named words

- status: works
- tags: sdata2,aggregate,asm
- scope: RPBoxScene
- source: RPBox_802c7924

symptom: retail has two 4-byte {-1} pool objects where s32 a[2]={-1,-1} makes one 8-byte object; struct-slot rewrites shift registers
cause: original had separate aggregate initialisers; no declaration order reproduces the schedule
fix: whole-function asm loading named const s32 words defined at the pool position (before the next named .sdata2 def)
