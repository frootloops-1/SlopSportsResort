# Hist reset loop of 30 vec3: int i=29 do-while

- status: works
- tags: loop,unroll,do-while
- scope: RPTns
- source: RPTns_80222a70

symptom: loop unrolled 6x even with opt_unroll_loops off
cause: for-loop form
fix: int i=29; do { hist[i].x=..; } while(--i>=0);
