# fn_801EF2F0 closed: FPR param-degree wall was a statement-order (pre-RA schedule) problem; brute-force statement permutations

- status: works
- tags: regalloc,fpr_replay,post-ra-schedule,statement-order,RPSports_801ef064
- scope: Pack/RPSports/RPSportsCommon/RPSports_801ef064
- source: claude/sp801ef-1103

symptom: retail width f29/margin f30/square f31, ours f30/f31/f29 with identical final instruction order; fpr_replay: width/margin degree 32=K
cause: MWCC schedules before AND after regalloc (backend-02 vs 07 differ), so the interference graph comes from the pre-RA order, which the post-RA scheduler then hides; removing the delta.y reload edge from width/margin fixed the callee-saved colours in the replay
fix: across = (width+margin)/len before along = (len+margin)/len (fixed f29/f30/f31), then all 24 orders of the center/delta statements (center.z first for the 0.0f pool) built in a loop: center.z, center.x, center.y, delta.x, delta.y = 100. Genuine source, no marker
