# mwcc @-ids are assigned per inline level: level-1 expansions first, nested locals after, new temps last

- status: works
- tags: regalloc,inline,vreg-numbering,new,RPBow
- scope: Pack/RPSports/RPBowScene/RPBow_8031641C
- source: claude/bow-8031641C-1105

symptom: fn_80316C7C: retail colours ball > count > 4 kokeshi mdl locals > mat; ours count > mat > mdl x4 > ball (high-degree group coloured by descending vreg)
cause: mwcc_dbg dumps: all level-1 inline expansion locals get @-ids in source order, then nested (level-2) locals, then new-expression temps, then optimizer temps. A wrapper inline pushes its nested callee's locals to level 2
fix: ball from static inline BowNewBall() whose local holds a hand operator new + ctor body (level-1 local, before count); material passed as an expression arg to nested inline BowSwapCull(mdl->mppMaterials[i]) (param becomes a level-2 @-var after the kokeshi mdl locals). Ball-loop region exact; fn harness 236 -> 219
