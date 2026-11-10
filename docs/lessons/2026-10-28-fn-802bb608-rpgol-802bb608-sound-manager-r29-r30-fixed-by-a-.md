# fn_802BB608 (RPGol_802bb608): sound-manager r29/r30 fixed by a static inline around the else body, but it needs auto_inline off and leaves the s7C tail open

- status: works
- tags: regalloc,gpr,inline,marker
- scope: RPGol_802bb608 fn_802BB608
- source: Gol units 2026-10-28

symptom: 99.0: RPSndAudioMgr instance pointer r30 (target r29) at 3 sound sites, 50 diff lines
cause: wrapping the else body (fn_80297088 .. fn_802BABE8) in static inline golRecordShot(w) makes on/res inline locals, so the manager pointer is coloured last and shares r29 with res
fix: golRecordShot + #pragma push/auto_inline off/pop around fn_802BB608 (else it auto-inlines into fn_802BBEB4, 100 -> 12): 99.5 only. NOT merged (marker + pragma for +0.5, function not closed); kept on branch claude/gol2-1028. Flat: named local per site, block-scoped on/res, anim+SE helper
