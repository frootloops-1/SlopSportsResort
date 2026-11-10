# Return of two !=1 checks: use && expression

- status: works
- tags: beqlr,bool
- scope: RPSportsCommon_unsplit

symptom: 25.5% with if/return chain for two early-return-on-1 checks
cause: branch layout
fix: return a != 1 && b != 1;
