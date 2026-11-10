# KPADInit constant regs: do-while init loop, reset loop needs inline scope

- status: works
- tags: KPAD,register,loop,inline,do-while
- scope: revolution/KPAD/KPAD

symptom: KPADInit 99.5: hoisted loop constants 0/40000/0xfd in wrong callee-saved order, second loop chan/ptr r25/r27 vs r27/r28
cause: for-loop vs do-while changes the hoisted-constant order; reset loop in target has its own inline scope
fix: i=0; do {...} while(++i<4) fixed loop 1 (99.8); static inline helper (MATCH-PENDING marker) around KPADSetObjInterval+reset loop -> 100. Block scope, chan=i reuse, decl order, store-order permutations (24) were all flat
