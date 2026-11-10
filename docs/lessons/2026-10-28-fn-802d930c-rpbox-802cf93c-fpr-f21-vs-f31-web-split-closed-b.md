# fn_802D930C (RPBox_802cf93c): FPR f21-vs-f31 web split closed by a static inline helper with the float as an inline param

- status: works
- tags: regalloc,fpr,inline,marker
- scope: RPBox_802cf93c fn_802D930C
- source: FPR experiment 2026-10-28, branch claude/fprA-1028

symptom: second assignment of sel gets f21 not f31; declaration order, separate var, statement order, a*= reuse all stay 99.93
cause: one-call FPR nodes are coloured after the many-call group and take the lowest-numbered already-used free callee-saved reg; a named local is coloured too late, an inline param is coloured before the f22 product temp and reuses T's dead f31
fix: static inline BoxHitImpulse(self, src, f32 imp, f32 c) around fn_801BA41C + three vel += imp*v stores, sel passed as imp; vx,vy,vz initialised at declaration in natural order (declare-then-assign swaps f1/f3). Marked MATCH-PENDING R17 + ledger row
