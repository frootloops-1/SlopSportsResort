# Both loads before first branch of a||b: load into locals first

- status: works
- tags: branch,or,load-order
- scope: RPTns
- source: RPTns_80235cd0

symptom: a->f==1 || b->f==1 short-circuits the second load
cause: plain || evaluates lazily
fix: int ha=A->f; int hb=B->f; if(ha==1||hb==1)
