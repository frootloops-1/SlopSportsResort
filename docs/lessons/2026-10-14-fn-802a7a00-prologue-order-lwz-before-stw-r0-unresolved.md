# fn_802A7A00 prologue order (lwz before stw r0) unresolved

- status: fails
- tags: scheduling,prologue
- scope: RPGolScene
- source: claude/rpgol-small

symptom: 86.4%: original loads o->f40 before stw r0,0x14(r1); ours loads the global first
cause: unknown
fix: Not found: temporaries in either order, bool return, reversed compare, float temp, inline literal, permuter 5 min (no real gain)
