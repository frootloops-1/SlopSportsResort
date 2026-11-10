# fn_802AA044 named m0/m1 locals vs inline helper temps decide colouring order

- status: works
- tags: regalloc,vreg-order,inline,RPGol_802a7a40,fn_802AA044
- scope: RPGol_802a7a40

symptom: loop locals r23..r27 shifted: target has m0>m1>cursor>symbases>i
cause: named locals are numbered at function start (lower vregs, coloured last); inline-helper temps are numbered later, so are coloured first and get higher regs
fix: replace named m0/m1 locals with a static inline GolClubInit(slot,a,b,i) helper: 99.3 -> 99.6. Scoping m0/m1 inside the loop regressed (99.1). Residual: o (new GolDbgStub) gets r26 not r28 because its vreg is numbered below the loop temps; moving o decl, GolRows(o) inline param, GolMakeStub inline did not change it
