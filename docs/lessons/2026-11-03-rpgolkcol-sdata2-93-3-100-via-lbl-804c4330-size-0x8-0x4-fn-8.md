# RPGolKCol: .sdata2 93.3 -> 100 via lbl_804C4330 size 0x8 -> 0x4; fn_802A4760 regalloc wall parked

- status: works
- tags: rpgol,golkcol,sdata2,symbols,regalloc,inline-recursion,parked
- source: claude/gol-4068-1103f 59573ff03

symptom: .sdata2 93.33 with 47/48 symbols exact; fn_802A4760 99.9 with a 16-byte DOL diff at 0x802a49e8
cause: lbl_804C4330 (0.1f) carried 4 bytes of trailing TU pad (next unit's .sdata2 is 8-aligned). fn_802A4760: three-register swap in one block of the inlined self-recursion (orig shift r14/node r20/v r21; ours r21/r14/r20); mwcc_dbg shows node(r108,@1345) coloured before shift copy (r107,@1346), target needs shift first
fix: symbols.txt size 0x8 -> 0x4 gives .sdata2 100, DOL stays 0 (same as 2026-10-14 pad lesson). fn_802A4760 parked (Opus): child local 98.7, s/child/o locals 90.6, const u8* node 99.4, u32 node flat, OR swap 96.2, if/else flat, inverted branch 61.6, 8+v / v+=8 flat, s32 shift flat, opt_propagation off 91.2, opt_lifetimes off 98.0, common_subs/dead_assignments/strength_reduction flat, permuter 9 min -j 6 flat (45 -> 45). Unit remaining: only fn_802A4760
