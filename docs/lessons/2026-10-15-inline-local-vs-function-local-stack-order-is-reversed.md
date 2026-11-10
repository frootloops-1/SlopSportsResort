# Inline-local vs function-local stack order is reversed

- status: works
- tags: mwcc,stack,inline
- scope: RPTns_8023c74c
- source: claude/rptns-2

symptom: MTX34 temps at swapped stack offsets (0x20 vs 0xb0)
cause: locals in an inlined body get ascending offsets in declaration order; plain function locals get descending
fix: inside inline declare a,b,c,mtx (lowest first); in a hand-expanded function declare mtx,c,b,a
