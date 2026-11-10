# Flip gate short by whole functions: mwld dead-stripped a vtable referenced only by an unrelocated raw constant (force_active)

- status: works
- tags: link,dead-strip,force_active,vtable,RPBowActiveBall,gate
- scope: Pack/RPSports/RPBowScene
- source: step2 2026-11-01

symptom: RPBowActiveBall flipped: dol_diff 630217 bytes, built 1152 short, sym_addr_check shows later functions shifted -1012/-1104
cause: lbl_803CA660 (ActiveBall vtable) is referenced only by a stack-spilled lis/subi raw constant at 0x80316E34 in NonMatching RPBow_8031641C (linked from asm); dtk made no relocation so nothing named it and mwld stripped the vtable and RenderModelSet/ResetRenderState/fn_8032A9E4/fn_8032ADF8. My first diagnosis (extra header static inlines in the .o, .text 1632 vs 1008) was WRONG: mwld strips those at link, Matching siblings emit the same 39
fix: symbols.txt: lbl_803CA660 ... scope:global force_active (or a config.yml add_relocations for 0x80316E34). Also fn_801C389C returns GXColor (not u32) and fn_801C37EC takes GXColor by value: removes the byte-extract wall (RenderModelSet, UpdateBallReturnRack). Do not compare .o section sizes; run the DOL gate and look at sym_addr_check shifts
