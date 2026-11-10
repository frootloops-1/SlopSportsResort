# RPSports_801f9150 split at 0x801FAC10: anchor confirmed; also needs .sdata2 0x804C20E8 split and lbl_803C2FE8 split into 4 PTMF objects

- status: open
- tags: data,split,ptmf,anchor,sdata2,objdiff,RPSports_801fac10
- scope: Pack/RPSports/RPSportsCommon/RPSports_801fac10

symptom: after splitting .text 0x801FAC10 / .data 0x803C2FD0 into RPSports_801fac10: .data 100, fn_801FB91C instructions and anchor offsets identical (addi r5,r31,0x24) but 99.2; fn_801FAF28 100.0 but not exact
cause: objdiff synthesizes R_PPC_NONE on the anchor-relative lwz/addi: target lbl_803C2FE8+0xC (one 0x30 symbol) vs ours sPm874a (separate 0xC static). FAF28's 1.0f is @3249 at .sdata2 0x804C20E8, inside the old unit's .sdata2 range (TU end pad at 0x804C20EC).
fix: pending orchestrator: splits.txt .sdata2 RPSports_801f9150 end:0x804C20E8, RPSports_801fac10 .sdata2 0x804C20E8-0x804C20F0; symbols.txt lbl_803C2FE8 size 0xC + three 0xC symbols at 0x803C2FF4/0x803C3000/0x803C300C (name the statics to match). Separate file-statics are required: a 4-element array loses the hoisted ...data.0 base (69.8). New unit emits in reverse source order.
