# SpMdlSetD r24/r25: inline-helper partitions cannot place a value in the new-temp window

- status: fails
- tags: register,vreg,inline,new,parked
- scope: RPSportsCommon/RPSports_801f1d4c
- source: claude/sp801f1-1104e 2e5f95b52

symptom: mgr/anm r24 vs retail r25; one-colour diff
cause: Needs a compiler temp created after loop-1 screen new and before the i*4 IV; named locals colour after all temps (r24), inline-helper vars colour early (r26/r28); helper defined after the ctor still expands early
fix: open: parked after 5 passes; variants in task note
