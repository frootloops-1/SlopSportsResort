# fn_8021BE50 closed: inline locals get vregs in REVERSE declaration order

- status: works
- tags: RPTnsScene,regalloc,inline,volatile,decl-order,MATCH-PENDING
- source: claude/tns5530-1103 0335e3666

symptom: fn_8021BE50 96.3: two inlined TnsRing::remove copies, same code, volatile regs rotated (ring r5 vs r6, t r6 vs r5, n/n2 r5/r7 swapped)
cause: volatile colouring = descending vreg, lowest free reg; ring (inline this) had the highest vreg. Inside a static inline, the locals' @ numbers follow REVERSE declaration order (declared t,r,n,p -> @p<n<r<t -> vreg t>r>n>p is wrong way round); coalesced webs take the LOWEST member vreg, so the n web (with the init next() temp) still colours before the next(n) temp n2
fix: static inline TnsRingRemove(TnsPl*,u32) declaring 'u32* p; u32* n; u32* m; TnsRing* r = self->ring; u32* t;' (gives t>r>m>n>p, 98.6 with decl order alone) and the inner increment written out into the declared local m (m = n + 1; if (m > r->end) m = r->begin; n = m) -> 100 (MATCH-PENDING R17, ledger 129). Member remove with r=this: 97.0
