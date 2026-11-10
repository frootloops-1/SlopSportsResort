# Locals declaration order affects regalloc

- status: works
- tags: regalloc,decl-order
- scope: RPSportsCommon_unsplit

symptom: fn_8020B368 89.3%
cause: stack/register order follows decl order
fix: declare zero buffer u32 blank[5] after the two temporaries
