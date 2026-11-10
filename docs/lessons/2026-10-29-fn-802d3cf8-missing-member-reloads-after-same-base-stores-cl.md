# fn_802D3CF8: missing member reloads after same-base stores closed by const-pointer loads (struct copy / const view)

- status: works
- tags: fn_802D3CF8,RPBox_802cf93c,cse,const,value-numbering,alias
- scope: RPBox_802cf93c
- source: claude/box802cf-r4-1029 opus

symptom: retail reloads self->f42C after v450 stores and w680 after a w4D8 store; ours reuses the first load (PCode value numbering disambiguates same-base different-offset stores, mwcc_dbg shows the reload present in initial code and deleted by the optimizer)
cause: VN only reuses a load whose instruction flags match; a load through a const pointer (or a struct-copy load) carries different flags, so the later plain load is not CSE'd with it
fix: self->v450 = *(BoxV3Pod*)&self->f42C (struct copy, member-wise lfs/stfs) -> 98.8; w680 & 4 read through a const BoxObj* (inline getter, MATCH-PENDING) -> 99.0. Remaining: clrlwi r10,16 on the u16 h arg of fn_802FDBCC (u32/int h do not produce it), GPR/FPR numbering
