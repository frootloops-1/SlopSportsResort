# fn_802C531C residue (RPGol_802c441c): four volatile pairs where the target colours the OLDER value first, opposite of the vreg-age model

- status: fails
- tags: regalloc,gpr,model
- scope: RPGol_802c441c fn_802C531C
- source: Gol units 2026-10-28

symptom: 98.9: golShotKindB result r3/field r4 swapped; shots r4/v r5/a r5 vs ours v r4/shots r5/a r4; golFollowT bool r3 vs pointer temps r4; fov remap in0=1000.0f f0 vs 0.0f literal f2
cause: all four reversed from the vreg-age prediction, which suggests one shared cause not yet found (possibly volatile colouring order or an inline-bool-before-expression-temps rule)
fix: none: getter for the state view v, sp helper variants, golCopyState inline, t as a call arg, decl/init forms, whole-body inline (27.7). Investigate the shared cause before more per-pair attempts
