# PlayerSelect SE colouring closed: member getSpeakerFlag() + nested-inline ranking

- status: works
- tags: regalloc,inline,colouring,RPSndAudioMgr,PlayerSelect
- scope: Pack/RPSports/RPSportsCommon/RPSysLytPlayerSelect_801DC37C
- source: sc801dc3-1102

symptom: fn_801DC4F0/DD798/DC784 99.5-99.8: str/id/flag callee-saved rotated in inlined startSystemSeWithRemote(name, RPSysPlayerMgr::instance()->getSpeakerFlag(-1)); fn_801DD798 state-3 loop index r29 vs r30
cause: free-function getSpeakerFlag(-1) call at the site gives flag/id the wrong vreg ranks; colouring is descending vreg and reuses the lowest already-used free callee-saved reg, so a non-interfering loop index lands in whatever reg the vreg just above it took
fix: member inline u32 SelectController::getSpeakerFlag() const { return RPSysPlayerMgr::instance()->getSpeakerFlag(-1); } with direct RPSndAudioMgr::instance()->startSystemSeWithRemote(lit, self->getSpeakerFlag()) closed fn_801DC4F0 alone (supersedes the 2026-11-02 fails lesson; check lesson 2026-10-08 first). For DD798: wrap CountControllers in an UpdateControllers inline (nested -> its vars rank below OpenWindowDone's i) and put the A_02 pair in a PlayDecideSe inline (nested SE -> name/id rank below count). 12/12, FLIP-OK
