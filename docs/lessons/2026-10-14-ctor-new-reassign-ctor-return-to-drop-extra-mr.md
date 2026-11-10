# ctor new: reassign ctor return to drop extra mr

- status: works
- tags: ctor,new
- scope: RPGol_802b8568
- source: fn_802B8E18

symptom: extra mr r29,r3
cause: ctor return ignored
fix: p = new T; if (p) p = ctor(p, ...);
