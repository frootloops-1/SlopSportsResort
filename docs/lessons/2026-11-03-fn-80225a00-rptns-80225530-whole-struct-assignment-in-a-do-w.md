# fn_80225A00 (RPTns_80225530): whole-struct assignment in a do-while shift loop gives memberwise copy with nested struct as lwz/stw block

- status: works
- tags: struct-copy,loop,unroll,implicit-operator=,RPTns
- scope: Pack/RPSports/RPTnsScene/RPTns_80225530

symptom: array shift loop: target copies scalar members typed (lwz/lfs) but the nested 16-byte TnsCtr member as lwz/lwz/stw/stw pairs; per-member source gives lfs/stfs for the nested member; for-loop with *d=*s fully unrolls
cause: MWCC implicit operator= of the outer struct copies scalar members typed and nested aggregate members as word blocks; for(i=3;i>0;i--) is a counted loop and gets fully unrolled (struct copy is small IR), a do-while with i-- then while(i>=1) is not
fix: int i = 3; do { self->a[i] = self->a[i - 1]; i--; } while (i >= 1); plus pass (f32)anm->v17(0,id) inline instead of a named int n (fixed lis r3 vs r5 for 0x4330): 91.9 -> 100. #pragma opt_unroll_loops off did NOT stop this unroll.
