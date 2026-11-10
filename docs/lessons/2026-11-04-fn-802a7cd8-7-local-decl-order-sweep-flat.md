# fn_802A7CD8 7-local decl-order sweep flat

- status: fails
- tags: regalloc,fpr,RPGol_802a7a40,fn_802A7CD8
- scope: RPGol_802a7a40

symptom: f27/f28/f30 colouring
cause: named float locals are not the lever
fix: fn_harness --perm over all 5040 orders of a,r,b,c,u,d,w (uninitialised decls, assigned later): all 22 diffs, no change
