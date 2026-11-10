# Bool helper: declare u32 flags local before bool result

- status: works
- tags: bool,regalloc,declaration-order,inline
- scope: RPTns_80246eec
- source: sonnet worker 2026-10-14

symptom: b/f registers swapped in static inline flag test
cause: declaration order drives register order
fix: u32 f = flags; bool b = false; in that order (fn_80246FA0/FD0)
