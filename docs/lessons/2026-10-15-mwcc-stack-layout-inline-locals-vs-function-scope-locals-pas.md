# MWCC stack layout: inline locals vs function-scope locals; pass expression to const VEC3& helper to make temporaries

- status: works
- tags: nw4r,ef,stack,inline,vec3
- scope: nw4r/ef

symptom: objdiff 99.7-99.9 with stack slot mismatch only
cause: function-scope locals top-down, inline-scope locals below; named locals vs temporaries land in different slots
fix: declare inline's local in caller and pass by reference; pass expr straight to const VEC3& wrapper; compare r1 offsets directly since objdiff barely reacts
