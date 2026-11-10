# static const char* const named string gets emitted to .sdata2 (not folded) and changes code

- status: fails
- tags: pool,string,rpsports
- source: sp8020f-1104

symptom: tried to pool N_scene_00 at parse time via a const pointer
cause: MWCC emits the const pointer object and loads it
fix: do not use; find another parse-time owner for the string
