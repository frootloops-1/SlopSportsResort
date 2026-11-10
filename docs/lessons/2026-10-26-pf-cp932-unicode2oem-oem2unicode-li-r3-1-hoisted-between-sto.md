# pf_cp932 Unicode2OEM/OEM2Unicode: li r3,1 hoisted between stores, temp in r5 not r3 (13 variants no gain)

- status: fails
- tags: pf_cp932,schedule,tail-call,args
- scope: revolution/VF/pf_cp932

symptom: Tail call Combine_Width(1,2) after a store of a computed temp: ours schedules li r3,1 before the last store so the temp lands in r5; target keeps temp in r3 and li r3 after the stores (98.6/97.6)
cause: Unknown pre-RA scheduling/IR-order difference; only affects the 2 branches that store a computed temp (pure-store branches match)
fix: No fix. Tried: temp local u16, +0xFEC0 / -0x140 / (u16) cast expression forms, swapped store order, s32 ret local before return, fn-ptr cast to (s32,s32), s16 w1/w2 locals, all 24 decl-order permutations of the 4 locals, #pragma scheduling off (much worse), u8/s8/no cast on the byte store
