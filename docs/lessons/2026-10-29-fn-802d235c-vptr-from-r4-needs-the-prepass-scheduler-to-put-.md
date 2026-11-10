# fn_802D235C: vptr-from-r4 needs the PREPASS scheduler to put lwz vptr before li r4 (peephole then forwards mr r3)

- status: open
- tags: fn_802D235C,RPBox_802cf93c,vcall,scheduler,mwcc_dbg
- scope: RPBox_802cf93c
- source: claude/box802cf-r2-1029 opus

symptom: virtual form: mr r3,r4; li r4,2; lwz r12,0x144(r3) vs target lwz r12,0x144(r4) first (96.6); explicit fn-ptr form gives r5 vptr (99.8)
cause: mwcc_dbg: codegen always emits mr r3,this; args; lwz r12,vptr(r3). Peephole (backend-06) forwards r3->source only if the source is not redefined before the lwz; in matched fn_802FD504 the prepass scheduler (backend-02) had moved lwz r12 above mr r4. Ours keeps li r4,2 first
fix: failed: const param (BoxObj* const), static inline BoxObjCheck2 wrapper, explicit pointer without named local (same 99.8). Untried: something that delays li r4 in the prepass list schedule
