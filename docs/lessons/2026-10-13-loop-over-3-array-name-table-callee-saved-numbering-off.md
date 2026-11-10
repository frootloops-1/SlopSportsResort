# Loop over 3-array name table: callee-saved numbering off

- status: fails
- tags: regalloc,loop
- scope: RPSportsCommon_unsplit

symptom: fn_8020F96C 94.1%: table base r31 vs r28
cause: unknown
fix: 5 variants tried (t-pointer, per-section pointer, reorder decls) no gain
