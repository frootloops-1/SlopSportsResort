# fn_802AA044 new-expression temp numbered after nested inline locals: make it an outer-inline local

- status: works
- tags: regalloc,inline,new,vreg-numbering,RPGol
- source: RPGol_802a7a40 2026-11-04 opus

symptom: 'o = new Stub' took r26 (handed to loop model ptrs) instead of r28
cause: @-vars are numbered newest-first; the new-expression null-check temp is created after the loop's GolClubInit locals, so it colours after them. Named fn locals number below every @-var (coloured last), so a named o does not help
fix: wrap loop+tail in an inline (loop index passed as int& so it stays a named fn local) and declare GolDbgStub* o at the top of that inline with a hand-written __nw__FUl/if(o){ct; vt=} instead of new: o is created before the nested GolClubInit locals. 99.6->100
