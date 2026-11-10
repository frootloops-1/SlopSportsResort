# Declare loop-body locals before the for so loop counter keeps early callee-saved reg; inline-result temp for row pointer (RPSports_80208744 3 fns -> 100)

- status: works
- tags: regalloc,simplify-order,inline-helper,data-defs,RPSports_80208744
- scope: RPSports_80208744

symptom: fn_80208814 98.8, fn_80208CA0 98.0, fn_802098D4 98.5; .rodata/.data 0%
cause: unit data undefined; stat-loop i simplified too early; row pointer coloured first
fix: Define unit tables at file end (const SpPair* params fixed CA0), descending order, getU32(6) pool order, u32 sport,game,s,g,stat declared at top, static inline SpGetOrder (R17 ledger 106). mwcc_dbg: simplify visits vregs ascending; nodes holding >=~29 neighbours stay in first colour set.
