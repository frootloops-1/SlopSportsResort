# MWCC stack layout: first-declared aggregate gets highest offset, matrices above vectors

- status: works
- tags: stack,locals,mwcc
- source: RPBox_802cf93c 2026-10-23

symptom: stack VEC3s off by 0xC; matrices in wrong order
cause: locals placed in declaration order downward; declaring all at function top controls it
fix: declare every local (incl. block-scoped ones) at top in descending target-offset order (fn_802D558C 95.6->97.7)
