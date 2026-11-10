# s7C = on ? 0 : 7 tail sharing 0 with prior b80=0 store

- status: open
- tags: golf,regalloc,constants
- scope: RPGol_802bca94
- source: opus-worker

symptom: target li r3,0 ... mr r0,r3; ours separate li 0 (fn_802BCA94 99.5, also fn_802BB608)
cause: target CSEs the zero constant across stores
fix: failed: ternary (branchless 94.3), m=7;if(on)m=0 (99.5), explicit zero var, bool type, static inline, if/else field stores (96.0), reorder before b80 (94.1)
