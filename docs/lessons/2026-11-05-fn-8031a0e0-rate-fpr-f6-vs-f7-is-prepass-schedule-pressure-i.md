# fn_8031A0E0 rate FPR f6 vs f7 is prepass-schedule pressure, insensitive to source order

- status: fails
- tags: fpr,schedule,lerp,RPBow_80319C98
- source: RPBow_80319C98 round 3

symptom: 4 rate lerps: retail keeps 6 temps live (rate f6), ours 7 (rate f7)
cause: prepass scheduler hoists all 8 prm loads; statement order is normalised
fix: Dead (harness flat 138-151): 24 statement perms, a+r*(b-a) / (b-a)*r+b, rate via inline helper return, f32 r copy, else-if clamps, rate clamps before f214 clamps. Also flat: 120 decl orders of flag/n/j/k/res for the tEF4 block
