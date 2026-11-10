# BsbMach ctor fn_8027FB5C 81.7 -> 100: build each BsbState record through its own pointer temp

- status: works
- tags: block-split,dead-store,vtable,ctor,100-instruction-block,RPBsb_8027e0b8
- scope: Pack/RPSports/RPBsbScene
- source: claude opus worker 2026-11-02

symptom: fn_8027FB5C 624 diff lines: retail keeps the dead base-vtable store only for st[12] (0x1AC), ours kept it at st[4]; _savegpr_21 vs _savegpr_20
cause: MWCC starts a new basic block once the current one passes 100 instructions at a statement start; a dead store survives only when the split lands between a record's base-vtable store and its derived-vtable store. Retail is a real ctor whose inlined member ctors keep this in a temp (one addi per record, 25 instead of 24 instructions)
fix: { BsbState* s = &self->st[i]; s->Init(); } for each record 0..12 (no dead stores, no dummy code). Also expected to close RPBsb_80285870 fn_80288E90 (84.3, 17 records) and replace the BsbStateClearKeepBase hack in RPBsb_80275a44 fn_80278D34. Diagnostic: standalone real-class test with unit flags + mwcc_dbg (~11 s). Pool order afterwards needed marker (void)0.0f; (ledger row 96) for .sdata2 0 before 8/100
