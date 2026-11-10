# fn_801E7EB4 FPR wall is pre-RA scheduling, not colouring

- status: fails
- tags: fpr,schedule,fpr_replay,RPSports_801E7EB4,fn_801E7EB4
- scope: Pack/RPSports/RPSportsCommon/RPSports_801E7EB4
- source: worker 2026-10-31

symptom: 99.3: target hw-quotient f2 / hh lfd f0, ours f0/f2; fpr_replay check reproduces our order
cause: target has HW=f0 and hh lfd B=f0, so pre-RA lfd B must come after fdivs X; our pre-RA scheduler hoists lfd B above fdivs (B interferes with HW). Renumbering alone cannot fix it
fix: none: hh inlined into Vector2f ctor arg -> B=f0,X=f2 but HW=f1 (94.8); named x=px/hw before hh (94.2). Plus 2026-10-28's 6 forms. Park; needs a source shape that delays the hh conversion load past the division
