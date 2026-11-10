# fabs without trailing frsp: local asm inline fabs

- status: works
- tags: fabs,float,frsp,asm
- scope: RPTns_8022e93c
- source: sonnet worker 2026-10-14

symptom: __fabs or (f32)__fabs adds frsp
cause: orig used an asm FAbs inline (nw4r-style)
fix: static inline asm f32 FAbs(register f32 x){ fabs ...} (RPTns_8022e93c fn_8022E998)
