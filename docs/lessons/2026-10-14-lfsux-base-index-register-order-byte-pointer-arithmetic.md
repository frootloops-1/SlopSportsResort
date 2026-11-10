# lfsux base/index register order: byte-pointer arithmetic

- status: works
- tags: lfsux,indexing,regalloc
- scope: RPTns_8022ef18
- source: sonnet worker 2026-10-14

symptom: lfsux with base r4 index r0 swapped
cause: base[idx] vs explicit byte offset changes operand assignment
fix: (u8*)base + idx*sizeof(T)
