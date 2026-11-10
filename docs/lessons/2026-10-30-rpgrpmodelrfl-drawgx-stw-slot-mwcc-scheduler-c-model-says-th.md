# RPGrpModelRfl DrawGX stw slot: MWCC Scheduler.c model says this-field load to DDATA store dep is unavoidable in-block

- status: fails
- tags: RPGrpModelRfl,DrawGX,mwcc,scheduler,alias,stw
- scope: RPGrpModelRfl::DrawGX

symptom: stw spDrawModel issued after lbzx/addi (ours) vs paired with lis right after lwz 0x94 (retail)
cause: ~/Downloads/mwcc-cuyler36/src/backend/Scheduler.c: a ptr-op load (any this->field, no memory object) gets add_dependency(load, later store, latency=load latency 2) to every later store whose object is DDATA (spDrawModel). Dual-issue 750 model: ours c0 lwz+li, c1 lis, c2 lbzx+addi, c3 stw. Retail needs stw ready at c1, i.e. NO lwz->stw dep: not reachable with lwz and stw in one pre-sched block in that order; store-first makes lwz wait on stw. mwcc_dbg shows pre-sched (01) order lwz,li,lbzx,lis,addi,stb,stw.
fix: fails (no change): int type=mMaterialType; spDrawModel=this; tevStageNum=TBL[type] (optimizer keeps lwz,stw,li,lbzx; scheduler still delays stw); const u8* tbl local; type=0; type|=mMaterialType; #pragma opt_pointer_analysis on/reset around DrawGX only (compiles, no effect); store-first regresses 99.7->98.9. Remaining hypothesis: retail had the store in a different pre-sched block or the load was not a ptr-op (memory object). SIZE-MISMATCH for RPGrpModel weak Set/IsJointVisible etc is an artifact (weak header copies, target defines them in RPGrpModel).
