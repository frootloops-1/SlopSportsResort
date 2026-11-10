# Transposed 3x4 -> vec3 copy with reverse-order loads

- status: works
- tags: mwcc,matrix,inline
- scope: RPGol_802b66c4
- source: sonnet-worker

symptom: z,y,x loads before stores; temp vec adds stack copies
cause: inline arg evaluation order
fix: static inline GolSet(GolV3*, x, y, z) called with m[0][i], m[1][i], m[2][i]
