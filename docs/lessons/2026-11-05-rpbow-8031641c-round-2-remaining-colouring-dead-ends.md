# RPBow_8031641C round 2: remaining colouring dead ends

- status: fails
- tags: regalloc,RPBow,dead-end
- scope: Pack/RPSports/RPBowScene/RPBow_8031641C
- source: claude/bow-8031641C-1105

symptom: fn_80316C7C field/kokeshi/blur colour residue; fn_80318EB0 obj/npcDb and officialDb order
cause: needs values to be @-vars at a specific inline level; source shape unknown
fix: Dead: per-site kokeshi wrapper inlines (worse), body/head void* loads (reload), field void*/hand new, decl-order perm of all fn_80318EB0 top locals (no effect), enum/u32 x,y, j-pick loop as inline (worse), void*/BowObj* typed new results
