# RPBow_8033B690 fn_8033DB38 fabsf calls regress vs __fabs

- status: fails
- tags: RPBow_8033B690,fn_8033DB38,fabsf,FPR
- scope: Pack/RPSports/RPBowScene
- source: 2026-11-05 Codex continuation of Claude worktree

symptom: The sphere collision velocity block differs in FPR register and stack-slot ordering.
cause: Explicit MSL fabsf calls change the inline expression and its temporary schedule substantially; the analogous fn_803395E4 result does not transfer.
fix: Tried fabsf(nw4r::math::VEC3Dot(...)) for vi and vj. All compiler versions regressed fn_8033DB38 from 97.4% to 90.3%. Reverted both calls and confirmed 97.4% remains.
