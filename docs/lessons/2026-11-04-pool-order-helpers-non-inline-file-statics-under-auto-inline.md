# Pool-order helpers: non-inline file statics under auto_inline on compile at their reverse-order slot

- status: works
- tags: string-pool,sdata2,pool-order,R17,RPSports_80201240
- scope: Pack/RPSports/RPSportsCommon/RPSports_80201240
- source: claude/sp80201-1104

symptom: W_face_01/N_AButton_00 and 0.0f pooled late (compile order) vs right after fn_80201240's literals
cause: static inline helpers pool at expansion; non-inline statics are compiled at their source slot
fix: #pragma auto_inline on; static fns between fn_802013D0 and fn_80201240 holding the literal + the 0.0f call; auto-inlined into the callers (R17 180)
