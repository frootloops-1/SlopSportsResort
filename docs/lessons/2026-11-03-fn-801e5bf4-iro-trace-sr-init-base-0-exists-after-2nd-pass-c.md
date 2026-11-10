# fn_801E5BF4 IRO trace: SR init base+0 exists after 2nd-pass constprop, IRO_DoTransformations drops +0, ExpressionPropagation then substitutes lbl

- status: fails
- tags: iv-init,iro,strength-reduction,DoTransformations,801E51B4,parked
- scope: RPSports_801E51B4
- source: decomp-hard 2026-11-03 sp801e5-1103

symptom: 2 lines: ours 'mr r29,r31' before 'mr r30,r26', retail 'mr r30,r26' then 'addi r29,r31,0'
cause: mwcc_frontend_trace --frontend-limit 200: after IRO_DoStrengthReduction (stage 59) loop-1 IV init is base+(i*12); 2nd-pass CopyAndConstantPropagation (62) makes it base+0; IRO_DoTransformations (64) removes the +0 -> copy base; IRO_ExpressionPropagation (103) replaces the copy by lbl (lis/addi), backend CSE makes mr. Loop 2 keeps base+0xa0 because ExpressionPropagation does not substitute into an add. Retail needs the zero to appear after the last DoTransformations or in a form it does not fold. A non-constant start (i = self->state after the store) gives mulli+add and the retail IV order (mr r30,r26 first), confirming the add form fixes order too.
fix: Dead (all 2 lines unless noted): label/goto before loop 1, opaque __rlwinm branch, real if(layout) branch (block theory is wrong: still mr), start=k local, rows=&base.p[k], &base.p[k+i*3], start=x-x / x*0 / x&0 / x^x (front end folds), Row struct views (3 forms), i*3+base.p, (u8*) byte offset, u32 i (4), (u32)/(s64) index casts (83+), chained self->state=i=0 (9), i=self->state (7: li+mulli+add). version_sweep: 3.0a5.2 is right. Open: a zero that becomes known only after stage 136 or that DoTransformations does not match.
