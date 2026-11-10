# fn_80211CB4: propagate const ScoreView* through callee param, ctx field and local (99.1 -> 100, no cast)

- status: works
- tags: const,prologue-schedule,RPSports_8020f530,propagation
- scope: Pack/RPSports
- source: claude 2026-11-02

symptom: param load lwz r5,0x10(r4) retail-scheduled in the prologue before the stack stores; ours after (2 diff lines)
cause: non-const pointee blocks hoisting. A plain const on the param alone fails to compile when the pointer is stored (ctx.score = score) or passed to a non-const callee
fix: const ScoreView* on fn_80211CB4, on the callee fn_802131C8 param, on the ctx struct field and on the local that reads it: no cast needed. A (ScoreView*) cast at the call also matches but is the worse spelling. Tried the same on 8 other read-only-pointer near misses (fn_802E6178 Box2Rec, fn_802E9974 BoxView worse 385 lines, fn_802D0404, fn_80281DA0, fn_802A4760, fn_802DFD4C, fn_802FD318, fn_80208CA0): no gain or the pointer is written/stored, so not const-able. fn_80281DA0 (f3 vs f2 fabs colouring) and fn_80208CA0 (struct return copy loads grouped) also failed decl order / return spellings.
