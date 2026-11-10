# fn_801F14F0 inline name/id r27<->r28 swap: forecast levers flat (parked 99.8)

- status: fails
- tags: fn_801F14F0,regalloc,forecast,RPSndAudioMgr

symptom: name ptr in r27 / id in r28 vs target r28/r27 in two inlined changeNameToIdRP blocks
cause: unknown; a-param reg (r28) reused by name in target, loop ptr r27 reused in ours
fix: failed: u32 id declared before name (flat); drop pName/mgr locals (99.8->90.7); separate name2 local for second call (->98.9). Diagnoser lever 1 flat, lever 7/3 not applicable.
