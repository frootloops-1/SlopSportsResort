# Hoist global field arg before ternary

- status: works
- tags: ternary,scheduling,hoist
- scope: RPSportsCommon_unsplit

symptom: 56.4%: original loads lbl->fC before the p8 ? p8->p10 : p1C branch
cause: arg evaluation order
fix: s32 game = lbl->fC; into a local before the select
