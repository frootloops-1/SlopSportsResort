# Float compare bool return: static inline taking (obj*, f32*)

- status: works
- tags: float,compare,bool,mfcr
- scope: RPTns_8023bb84
- source: sonnet worker 2026-10-14

symptom: srwi r3,r3,31 instead of mfcr/extrwi, or swapped load order; plain return x<y 90%
cause: operand evaluation order and inlining shape
fix: static inline bool f(obj* o, f32* p){ f32 a=o->x; f32 b=*p; return a > b; }
