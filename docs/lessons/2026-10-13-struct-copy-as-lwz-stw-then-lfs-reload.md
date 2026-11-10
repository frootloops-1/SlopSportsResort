# Struct copy as lwz/stw then lfs reload

- status: works
- tags: copy,struct,lwz,float
- scope: RPGol_802c441c
- source: claude/rpgolscene-unsplit

symptom: orig copies a float vec3 with lwz/stw and reloads with lfs; ours forwards floats
cause: float-typed struct copy
fix: *(struct{u32 w[3];}*)&dst = *(...)&src
