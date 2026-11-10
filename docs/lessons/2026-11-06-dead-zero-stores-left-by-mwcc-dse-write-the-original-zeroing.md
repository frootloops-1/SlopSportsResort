# Dead zero stores left by MWCC DSE: write the original zeroing loop, not the survivors (fn_80323F30 closed)

- status: works
- tags: scheduler,dse,dead-store,fn_80323F30,RPBow_80323790,select_ready_node
- scope: RPBow_80323790/fn_80323F30
- source: claude/bow-80323790-1105 2026-11-06

symptom: 98.4 pool-load schedule wall: 3 dead zero stores (A0,B0,A1) interleaved among loads; select_ready_node model 'proved' target infeasible
cause: The 3 stores are survivors of a dead-store pass over an interleaved zeroing loop A[i]=0;B[i]=0 for i<5 (A=g+0x26c,B=g+0x294). Eliminated stores still shape the DAG the scheduler sees, so writing only the survivors can never reproduce the order. n=1..4 and 10 give different survivor sets/schedules.
fix: for (s32 i = 0; i < 5; i++) { A[i] = 0.0f; B[i] = 0.0f; } at the old zero-store spot -> 100. General: when a function has odd partial dead stores, try the natural full init (loop/all elements, various N) and look at which survive.
