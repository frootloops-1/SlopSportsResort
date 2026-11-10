# Pool order when the last-in-text fn's literals lead the pool

- status: works
- tags: sdata2,pool,placeholder
- scope: RPTns_8022a17c

symptom: 3 fns 99.9 from pool relocs (orig pool starts with fn_8022A614's literals, which is last in .text)
cause: pool follows codegen order; source order fixes text order only
fix: move the math into a static inline and call it from an unreferenced static fn placed LAST in source (adds 0x4C local text in .o; check before a Matching flip)
