# Compare call results inline, not via a typed local

- status: works
- tags: mwcc,u16,s8,extension,compare
- scope: RPSportsCommon_unsplit

symptom: u16/s8 call result stored in a local first gives raw mr then re-extends at compare (clrlwi/extsb after the mr)
cause: Original compared f(a) < g(a) directly; extension happens right after the call into the saved reg
fix: Write the comparison with both calls inline, g() (the saved reg) evaluated first
