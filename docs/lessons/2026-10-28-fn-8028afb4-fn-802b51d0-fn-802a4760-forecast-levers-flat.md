# fn_8028AFB4/fn_802B51D0/fn_802A4760 forecast levers flat

- status: fails
- tags: forecast,regalloc,fn_8028AFB4,fn_802B51D0,fn_802A4760
- scope: fn_8028AFB4 fn_802B51D0 fn_802A4760

symptom: flags/slwi (r27/r29) swap; ball/pin (r26/r28) swap; inlined recursion node/shift/off rotation
cause: post-RA colouring order not steerable by listed levers
fix: fn_8028AFB4: u32 flags, flags declared first, inline getResFlags accessor, flags after cnt: all flat or worse. fn_802B51D0: GetBallPos accessor 99.2 (worse), GetPin accessor flat, ply local flat. fn_802A4760: node+=v before shift-- flat, separate u32 w for offset 98.9. Parked.
