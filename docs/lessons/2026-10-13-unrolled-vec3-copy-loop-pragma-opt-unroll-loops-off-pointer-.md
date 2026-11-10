# Unrolled vec3 copy loop: pragma opt_unroll_loops off + pointer do-while

- status: works
- tags: mwcc,loop,unroll
- scope: RPGol_802b614c
- source: sonnet-worker

symptom: orig plain bge loop; ours unrolled or ctr loop
cause: MWCC loop unrolling
fix: #pragma opt_unroll_loops off around a pointer do-while (int countdown fully unrolled, pointer for gave ctr loop)
