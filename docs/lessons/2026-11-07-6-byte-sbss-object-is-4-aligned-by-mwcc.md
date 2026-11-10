# 6-byte .sbss object is 4-aligned by MWCC

- status: works
- tags: sbss,align
- scope: RPBsbScene
- source: RPBsb_8027039c

symptom: char x[6] / u16 x[3] lands at +4 instead of retail +2 after two chars
cause: MWCC aligns the object to 4 regardless of element type
fix: one struct for the neighbouring small objects; macros keep the C names; asm uses block+off
