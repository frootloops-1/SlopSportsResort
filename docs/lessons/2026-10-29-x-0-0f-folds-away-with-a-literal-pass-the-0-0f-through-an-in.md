# x - 0.0f folds away with a literal; pass the 0.0f through an inline param

- status: works
- tags: rpbox,802c7d08,sdata2,float-literal,inline
- scope: RPBox_802c7924
- source: x-golbox-1029

symptom: Replacing an extern const f32 zero with the literal 0.0f dropped an fsubs (d = dot - 0.0f) and cost fn_802C7D08 1%, size 1624 vs 1616
cause: MWCC folds x - 0.0f for a literal; an extern load is opaque
fix: give the static inline BoxProject a f32 off parameter and pass the 0.0f literal at the call site; the sub survives and the 0.0f is CSE'd with the earlier compare constant
