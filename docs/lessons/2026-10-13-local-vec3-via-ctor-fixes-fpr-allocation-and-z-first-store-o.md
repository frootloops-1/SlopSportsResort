# Local VEC3 via ctor fixes FPR allocation and z-first store order

- status: works
- tags: mwcc,vec3,float,regalloc
- scope: RPGol_802b614c
- source: opus-worker

symptom: field-by-field local VEC3 from stack float params: wrong FPRs and store order
cause: ctor(x,y,z) inline changes order
fix: local struct deriving VEC3 with ctor setting x,y,z
