# fn_802DD1F0: literal 0.0f lets stw old issue before lwz pE4; the extern works via the scheduler's DDATA memory dependency

- status: open
- tags: fn_802DD1F0,RPBox_802cf93c,scheduler,lbl_804C4E10
- scope: RPBox_802cf93c

symptom: with f32 zero = 0.0f (or BoxSeq32::Reset) one stw r20,0x80 moves above lwz r3,0xe4 (99.0); extern f32 lbl_804C4E10 read is exact but unresolved at link
cause: Scheduler.c add_memory_dependencies: pointer stores depend (with latency) on earlier reads of DDATA objects; a pool literal load is not DDATA, so the first store is ready at once
fix: failed: literal zero, seq.Reset(1/0/0) inline (both 99.0). Untried: another memory read (not pool) before the stores, e.g. a member load used as the zero
