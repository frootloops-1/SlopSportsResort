# fn_80350278 (RPBow_803501D8): const ctx + inlined const accessors for pScore/frames + loops written directly + one-expression bool; wstring pool merge fixes .rodata reloc names (R17 rows 45-46)

- status: works
- tags: rpbow,80350278,const,accessor,iro-temp,wstringbase0,r17
- source: worker cs2 + orchestrator 2026-11-01

symptom: 148 lines: throw-loop pScore r27 vs target r29 and SR pointers shifted; anim In/Out loops frames/row pointers/i/j wrong; .rodata @278/@280 relocs point into one @wstringBase0 instead of the target's separate lbl_ symbols
cause: named locals are numbered below IRO strength-reduced pointers; static inline row helpers make j a high frontend temp (@501) coloured first; reverse as false+if-assign stays a named local
fix: const BowScoreCtx* ctx (148 -> 116); pScore via inlined const accessor ctx->GetFrameScore(p, f) (R17, same effect as BowBitRef holder); anim loops written directly (no BowRowStartIn/Out helpers) so j is a named local below i; bool reverse = side != 0 && mode == 0; one expression; s32 frames = ctx->GetAnmFrame() inlined const accessor (R17). Config: merge symbols.txt lbl_804BE974..lbl_804BE9C2 (20 wide/short strings) into one @wstringBase0 .sdata:0x804BE974 size 0x5C scope:local -> .rodata 68 -> 100. Unit still NonMatching: .data lumped (27 tables of ~12 RPBow units, see docs/tasks/RPBowScene.md).
