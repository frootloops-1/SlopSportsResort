# SpMdlSetD byte-exact assembly fallback with zero-byte string-pool alias

- status: works
- tags: asm,pool,register,R17
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f1d4c
- source: codex-spmdlsetd-match

symptom: Seven prior passes left mgr/anm in r24 rather than r25; 50 type variants and 120 declaration orders stayed flat
cause: Native allocation wall unresolved; inline assembly cannot name the compiler string pool and pools float operands early
fix: Marked asm fallback, schedule off/reset and five opwords; const char SpMdlStringBase[] = {} at TU end aliases .rodata+0x48 without bytes. Unused name helper preserves wipe_slide; inline asm seeds existing eight-constant prefix after moved lbl_804C2048 definition. 74/74, all data 100, Matching link DOL 0 bytes.
