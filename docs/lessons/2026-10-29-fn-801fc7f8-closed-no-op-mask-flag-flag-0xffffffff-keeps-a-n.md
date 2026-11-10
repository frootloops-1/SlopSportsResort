# fn_801FC7F8 closed: no-op mask 'flag = flag & 0xFFFFFFFF' keeps a named flag local alive below limit

- status: works
- tags: fn_801FC7F8,regalloc,r0,vreg-numbering,forward-substitution
- scope: RPSports_801fc7f8
- source: claude/fc7f8-1029

symptom: limit r4 / flag load r0 vs target limit r0 / flag r3; every single-def flag local (incl dead-init, reuse of c or b, flag=flag, flag &= ~0) is forward-substituted by the front-end so the load stays a high-numbered temp coloured first
cause: colour order is descending vreg; a surviving named local declared after limit gets a lower number than limit, so limit is coloured first and takes r0
fix: s32 flag = load; flag = flag & 0xFFFFFFFF; if (flag == 0) limit = 1200; with flag declared AFTER limit (before limit fails): 12 -> 0, 14/14 exact. Only the explicit '= flag & 0xFFFFFFFF' form works; '&=' , 'flag = flag', '| 0' with dead init, and the mask inline in the compare all stay at 12 (R17 marker)
