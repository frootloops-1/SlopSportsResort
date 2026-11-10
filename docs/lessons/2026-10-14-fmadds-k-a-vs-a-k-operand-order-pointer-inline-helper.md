# fmadds k*a vs a*k operand order: pointer inline helper

- status: works
- tags: float,fmadds
- scope: RPGol_802b7df8
- source: fn_802B8320

symptom: fmadds operands swapped, inline rewrites no help
cause: expression shape
fix: static inline ScaleAdd(V* o,const V* d,float k,const V* p){ o->x = d->x*k + p->x; ...}
