# Vec copy back is store-forwarded; struct assignment emits lwz/stw (RPGol_802a3a6c)

- status: works
- tags: rpgol802a3a6c,struct-copy,store-forwarding
- scope: RPGol_802a3a6c
- source: sonnet

symptom: field-wise copy of constants disappears (38.8%)
cause: MWCC forwards stored constants
fix: g->copy = g->axes struct assignment -> 67.5%; savegpr_27 per-subobject pointer shape still open
