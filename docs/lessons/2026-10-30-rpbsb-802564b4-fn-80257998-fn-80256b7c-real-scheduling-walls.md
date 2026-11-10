# RPBsb_802564b4 fn_80257998/fn_80256B7C: real scheduling walls, not phantom relocs

- status: fails
- tags: RPBsb,schedule,unroll,induction,lfs,store-alias,park
- source: worker bsb564b 2026-10-31

symptom: fn_80257998 99.44: in 8x-unrolled mat-colour loop, 'addi r4,r4,8' (i+=8) lands one iteration later than target (target iter6 after lbz 1(r3)); fn_80256B7C 97.54: target loads lfs lbl_804BF78C before stw hit->ignoreId (after lbz flag, li 2) and fadds after stw; ours loads it after the vtable lwz. objdiff rows confirm real reorder (no R_PPC_NONE phantom).
cause: Unknown. mwcc_dbg pre-sched IR shows 'addi r51(off),0x20; addi r57(i),8' at loop end; only scheduler tie-break differs. For B7C, any source that puts the lbl load before the store gets it hoisted above lbz/li (95.4).
fix: Failed (no gain): loop-var decl inside for, member-wise colour copy, inline SetMatColor(const&), *(mats+i), i++ in index (73.8), u16 n (97.8); B7C: sum/load into local before/after store, operand swap, ret=0 before store, inline v0C wrapper, s32 two local, flag/radius order swap. Parked.
