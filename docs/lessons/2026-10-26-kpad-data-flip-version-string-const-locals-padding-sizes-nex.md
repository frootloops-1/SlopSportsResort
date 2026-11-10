# KPAD data flip: version string, const locals, padding sizes, next-unit align

- status: works
- tags: data,symbols,sdata2,bss,version,align
- scope: revolution/KPAD

symptom: unit 100% code but .data 85, .bss 50, .sdata2 88, DOL shifted -24 after flip
cause: #if (VERSION == A || B) with undefined VERSION is true so wrong version string; const f32 locals emit name$N sdata2 objects; symbol sizes included tail padding from next unit alignment (WPAD ALIGN(32) stack)
fix: write the retail string; use inline constant expressions; shrink symbols to compiler sizes and add align:32 on the next unit's .bss in splits.txt; -0.2f/0.2f pool slot via dead literals (MATCH-PENDING R17)
