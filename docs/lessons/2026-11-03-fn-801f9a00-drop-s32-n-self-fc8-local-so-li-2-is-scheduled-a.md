# fn_801F9A00: drop s32 n=self->fC8 local so li 2 is scheduled after rlwinm

- status: works
- tags: scheduler,pre-ra,mwcc_sched_trace,RPSports_801f9534
- scope: MWCC GC/3.0a5.2 pre-RA scheduler

symptom: lbz r5/rlwinm r5,r5 vs retail lbz r0/rlwinm r5,r0; li r0,2 issued one slot before the rlwinm
cause: pre-RA list scheduler picks by height; s32 n local put lwz fC8 in the same block after the play-mode stb (memory dep), giving li 2 height 5 > j==0 cmpi height 3
fix: read self->fC8 directly in the unrolled loop condition/store; the load moves behind the j==0 branch, li 2 height drops to 3. Diagnosed in one run of tools/mwcc_sched_trace.py (candidate heights per cycle). General: when an li constant is hoisted one slot too early, look at what follows its store in the same block
