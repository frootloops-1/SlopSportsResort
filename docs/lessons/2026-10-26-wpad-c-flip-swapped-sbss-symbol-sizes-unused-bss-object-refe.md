# WPAD.c flip: swapped sbss symbol sizes, unused bss object, reference loop form

- status: works
- tags: wpad,symbols,sbss,bss,flip,register-swap

symptom: WPAD.c 67/68 fns, reloc diffs _afhCnt vs _extCnt, .bss 99.49%, RetrieveChannel r30/r31 swap
cause: symbols.txt had _extCnt/_afhCnt swapped with wrong sizes (u16 at D6, u8[4] at D8); missing 0x48 unreferenced bss; s16/u32 index casts
fix: fix symbols.txt sizes (afhCnt D6 x2, extCnt D8 x4, rumbleCnt x4, chan_active_state x4); add u8 __WPADUnusedBss[0x48] after _wpd; RetrieveChannel: s32 i, regist[WUD_MAX_DEV_ENTRY_FOR_STD+i] in first loop (from external WPAD.c reference). DOL 0 bytes
