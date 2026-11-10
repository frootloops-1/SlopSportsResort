# Hoisted li r31,0 shared with earlier zero store: inline if/else bool form

- status: works
- tags: mwcc,const,cse,inline
- scope: RPGolDrawManager

symptom: fn_802946DC: orig li r0,0 store + per-inline li r31,0; ours hoisted li r31,0 used by both
cause: early-return inline lets CSE reuse the zero
fix: inline bool f(){bool r; if(a()) r=true; else { r=false; ... } return r;}
