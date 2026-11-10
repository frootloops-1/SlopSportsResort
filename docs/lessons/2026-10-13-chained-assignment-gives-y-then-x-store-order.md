# Chained assignment gives y-then-x store order

- status: works
- tags: mwcc,stores
- scope: RPGol_802b614c
- source: opus-worker

symptom: orig stores y then x of same value
cause: right-to-left chained assignment
fix: n->x = n->y = 0.0f
