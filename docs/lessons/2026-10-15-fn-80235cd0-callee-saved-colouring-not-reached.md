# fn_80235CD0 callee-saved colouring not reached

- status: fails
- tags: regalloc,permuter
- scope: RPTns
- source: RPTns_80235cd0

symptom: st/other/e registers rotated
cause: unknown
fix: 120 declaration orders and 8 min permuter gave nothing; mixed per-loop/function-level i best (99.2)
