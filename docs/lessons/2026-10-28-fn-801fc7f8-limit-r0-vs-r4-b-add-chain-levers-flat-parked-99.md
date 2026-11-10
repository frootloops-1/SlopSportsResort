# fn_801FC7F8 limit r0 vs r4 / b add chain: levers flat (parked 99.65)

- status: fails
- tags: fn_801FC7F8,regalloc,forecast

symptom: target limit in r0, flag load into r3; ours limit r4, load r0, add into r27
cause: unknown
fix: failed: ternary limit (flat); (a>limit?limit:a) inline clamp (99.6->99.5, worse add chain). Diagnoser lever 9 (named const local) irrelevant.
