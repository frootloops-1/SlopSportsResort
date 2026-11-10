# Group-of-state-objects ctor: temp member pointer and return self

- status: works
- tags: ctor,regalloc,new
- scope: Pack/RPSports/RPTnsScene/RPTns_802338a4

symptom: member init addi r3,r14,N + stw vt,N-4(r14) instead of addi r15 / mr r3,r15 / stw 0(r15); tail missing mr r3,r30 with r6 for last new
cause: target keeps &g->m[i] in a saved reg (inline-ctor shape); function is a ctor returning this
fix: { void** m = &g->m[i]; base_ctor(m); *m = vt; } per member; return self. The 29 state stores with stack spills matched as plain sequential assignments
