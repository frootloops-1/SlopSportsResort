# Constant-trip loops: do-while is not unrolled, for/while are

- status: works
- tags: loop,unroll,ctr
- scope: mwcc
- source: RPTns_802390b0

symptom: orig li r5,0x4ff ... subic./bge; ours mtctr + 8x unrolled body
cause: MWCC unrolls for/while loops with a constant trip count
fix: int i = 0x4FF; do { ... } while (--i >= 0);
