# fn_802C698C r0/r3 swap in inlined RPSysLytAnmObj::restart tail

- status: open
- tags: regalloc,r0,inline,restart
- scope: RPGol_802c68a4
- source: claude/rpgolscene-unsplit

symptom: 99.8: arg->idx temp and lha/xoris frame temp registers swapped
cause: unknown; register allocation
fix: failed: decl order/scope of n and a, inline helper, restart via fields, f32 temp, explicit cast, reference/pointer temp (worse); permuter next
