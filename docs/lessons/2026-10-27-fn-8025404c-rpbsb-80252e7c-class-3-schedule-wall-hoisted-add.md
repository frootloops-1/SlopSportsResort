# fn_8025404C (RPBsb_80252e7c): class-3 schedule wall, hoisted addi vtable+0x24 takes r0 so li 8 lands in r4; no source lever, 10-min permuter no gain

- status: fails
- tags: RPBsb_80252e7c,fn_8025404C,register,schedule,permuter,InitSoundBase,F6
- scope: Pack/RPSports/RPBsbScene/RPBsb_80252e7c
- source: orchestrator-1027

symptom: 98.7%, 5 lines at 0x8025429C: target li r0,8, ours li r4,8; ours hoists addi r0,vtbl,0x24 before lfs f0, target has it after stw r0,0x44 (tail after __construct_array in the second InitSoundBase block, snd88 size 0x78)
cause: pre-RA scheduler hoists the vtable-offset addi above lfs so r0 is busy; call set and control flow identical
fix: failed (second round): drop local void** vt and write both vtable stores directly (byte-identical), ascending 0x6c/0x70 float stores (10 diff lines), chained int store in InitSoundBase (identical); permuter C++ stand-in (setup --keep-bodies --name fn_8025404C --static, PERMUTER_DIR=~/Downloads/decomp-permuter when running from a /tmp worktree) base 75, 3141 iters/10 min -j 6, only ties. Untried: moving the snd88 block into its own static inline helper.
