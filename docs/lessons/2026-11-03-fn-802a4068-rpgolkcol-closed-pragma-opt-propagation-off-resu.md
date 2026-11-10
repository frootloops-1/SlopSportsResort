# fn_802A4068 (RPGolKCol) closed: #pragma opt_propagation off + result local (MATCH-PENDING R17 row 152)

- status: works
- tags: rpgol,golkcol,opt_propagation,pragma,prologue,mwcc_dbg,r17
- source: claude/gol-4068-1103f 1fbac2f06

symptom: 88.7%: prism pointer sunk to call arg (ext copies first), last edge test folded to mfcr/extrwi/cntlzw
cause: Sinking is done by the front-end optimizer (propagation), not scheduler/RA: mwcc_dbg backend-00 already shows the prism sunk
fix: #pragma push / opt_propagation off / pop around the fn, direct GolKPrism* prism=&k->prisms[*k->cur]; GolKPrismExt* ext=&k->ext[*k->cur]; (prisms/extensions/index locals leave r7/r8 swap 96.4), and int result=0 returned by the three early exits + final return 1 (with prop off a trailing if(c) return 0; return 1 still folds; result var keeps the branch form). Dead: opt level 0/1 worse (74/77), 2/3 no change; file-wide prop off regresses 5 fns; opt_dead_assignments off alone 93.5; common_subs/lifetimes/strength_reduction/dead_code/optimize_for_size no change; goto/nested/|| tails 86-96.8. Pragma is a steering marker, retail source probably lacks it. General lever: when mwcc_dbg shows the wrong IR order already in backend-00, try opt_propagation off scoped to the one function
