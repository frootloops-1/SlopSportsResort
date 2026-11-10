# fn_802D235C/fn_802D7920: prepass latency-filler explanation of the remaining walls

- status: open
- tags: fn_802D235C,fn_802D7920,prepass,scheduler
- scope: mwcc GC/3.0a5.2
- source: mwcc_dbg backend-00/02 dumps

symptom: D235C: lwz r12,0x144(r4) must precede mr r3,r4/li r4,2; D7920: li base must not interfere with r3 (mr r3,self sits between li and lfs 4(base) pre-RA)
cause: D235C: genuine other->v40(2) pcode is mr r3; li r4,2; lwz r12,0x144(r3). Prepass picks li to fill the mr->lwz latency, so peephole cannot forward r3->r4 (r4 redefined). Target needs mr; lwz; li. Manual vtable forms give the right order but colour the vptr r5 (genuine vcall uses phys r12). D7920: pre-RA mr r3,self is chosen as a latency filler before lfs f37,4(r37)
fix: untried: make the li r4,2 arg not ready at cycle 1 (depend on a late value); single-vreg reassigned function-pointer spellings (void*/HitFn/u32) are identical to 4 lines
