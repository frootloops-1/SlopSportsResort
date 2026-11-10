# fn_801EF4B8 closed: n-1 as expressions in loop 1, counter i reused for loop 2, n-- bound

- status: works
- tags: regalloc,two-webs,licm,sweep,RPSports_801ef064
- scope: Pack/RPSports/RPSportsCommon/RPSports_801ef064
- source: claude/sp801ef-1103

symptom: named last had to be numbered above the loop temps (xor, colour word) and j had to colour before i
cause: a named local gets a low vreg; an LICM-hoisted n - 1 and a variable's second web get late numbers
fix: first loop SpGraphPoint(..., n - 1, i) / while (i <= n - 1); i = 0 again for the second loop (or declare s32 j at the top); last = n - 1 only for the second loop's first point; n-- bound -> 100
