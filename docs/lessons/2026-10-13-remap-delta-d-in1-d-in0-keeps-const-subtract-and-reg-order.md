# Remap delta: d = in1; d -= in0 keeps const subtract and reg order

- status: works
- tags: float,fold,remap
- scope: RPGol_802c441c
- source: claude/rpgolscene-unsplit

symptom: d = in1 - in0 folds; hi=in1; d=hi-in0 gives wrong register
cause: constant propagation / vreg order
fix: float d = in1; d -= in0; (fn_802C531C)
