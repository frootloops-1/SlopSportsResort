# fn_802C0C50 self/n/arg callee-saved rotation

- status: open
- tags: regalloc,callee-saved,rotation
- scope: RPGol_802c0c38
- source: claude/rpgolscene-unsplit

symptom: 99.3: orig self=r31 n=r30 arg=r25, ours r30/r25/r31; r0/r3 swap in inner loop
cause: unknown
fix: failed: 350 random decl orders, alias locals, member fn, inline helpers, accessor inlines, row pointers; permuter next
