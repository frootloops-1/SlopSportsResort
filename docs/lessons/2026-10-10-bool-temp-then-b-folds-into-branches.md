# BOOL temp then !b folds into branches

- status: works
- tags: metrotrk,support
- scope: MetroTRK/debugger/Portable/support.c
- source: subagent decomp-standard, verified by orchestrator

symptom: !b argument compiled as branches
cause: mwcc folds BOOL b = read && x; f(!b)
fix: use b == 0 for the cntlzw/srwi sequence
