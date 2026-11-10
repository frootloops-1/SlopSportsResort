# fn_80313F60 const-1 vs w8 load r0 colouring: source variants flat

- status: fails
- tags: regalloc,vreg-order,RPBow,fn_80313F60
- scope: Pack/RPSports/RPBowScene/RPBow_80313028
- source: claude/nm-3028-20261031

symptom: target li r0,1 live across lwz r3,8(r3); ours li r4,1 and lwz r0
cause: mwcc_dbg: const vreg r48 < reloaded w8 vreg r50 so w8 coloured first (r0); target needs the const coloured first
fix: failed: plain 1, bool true, named u8/s32/bool local, static-inline helper with param, p->b138=p->w124 (92.8), ternary (95), negated if (97.2), regsearch --generic (flat)
