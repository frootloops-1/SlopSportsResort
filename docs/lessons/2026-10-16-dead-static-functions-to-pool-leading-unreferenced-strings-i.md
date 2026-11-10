# dead static functions to pool leading unreferenced strings in order

- status: works
- tags: rodata,pool-order,dead-strip,rpbsb
- source: RPBsb_8027c2f0 2026-10-16

symptom: pool offsets all shifted by a constant
cause: missing/misordered unreferenced strings
fix: defer_codegen off, ascending order, dead static fns placed between pointer globals to pool unused strings
