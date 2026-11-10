# fn_80200600 (RPSports_801ffec0) parked 99.9: retail needs a/else-IV numbered between first-loop r and i

- status: fails
- tags: regalloc,color_sim,numbering,RPSports_801ffec0
- scope: Pack/RPSports
- source: claude/sp801ff-1103

symptom: two-branch a r28 vs r29, else-loop IV r30 vs r29
cause: colour order is descending vreg for low-degree nodes; a/IV must colour after r (r29) and before i1 (r28), i.e. vreg between r45 and r44, impossible with program-order local numbering
fix: failed: fn-level i or r/a/i, row-body or whole-loop inline helper (pos stack slot moves too), play-last/TV/SetFwd inlines, SpV3 v moved into loop, regsearch --generic 12 min flat
