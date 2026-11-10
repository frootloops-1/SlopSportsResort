# const array bound reload in unrolled zero-fill

- status: works
- tags: mwcc,loop,unroll

symptom: 8x unrolled fill loop CSEs the bound into a register
cause: non-const local array
fix: const s32 sizes[] so bound is reloaded each loop like the original
