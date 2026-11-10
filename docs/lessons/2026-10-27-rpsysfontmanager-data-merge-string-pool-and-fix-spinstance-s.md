# RPSysFontManager data: merge string pool and fix spInstance size gives .data/.rodata/.sbss 100

- status: works
- tags: symbols,string-pool,sbss,RPSysFontManager
- scope: Pack/RPSystem/RPSysFontManager
- source: claude/fontmgr-1027 2026-10-27

symptom: .data 70%, .sbss 50% with all code exact except LoadResFonts.
cause: 7 per-string lbl_ symbols made RES_FONT_NAMES relocs differ from our @stringBase0; spInstance listed as 8 bytes (4 + pad).
fix: Replace lbl_ strings with one @stringBase0 (size 0xA4, data:string_table); spInstance size 0x4. LoadResFonts r29/r30 swap remains: 25+ source variants and other-structure tries gave no gain (14 diff lines).
