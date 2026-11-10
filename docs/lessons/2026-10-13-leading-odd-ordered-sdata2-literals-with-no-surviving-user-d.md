# Leading/odd-ordered sdata2 literals with no surviving user: dead static placeholder fns

- status: works
- tags: sdata2,deadstrip,pool,order,placeholder
- scope: RPGol_802c441c
- source: claude/rpgolscene-unsplit

symptom: target pool has literals no linked fn loads, or order differs from first use by surviving fns
cause: original had auto-inlined helpers / small fns that the linker dead-stripped; their literals stayed in the pool
fix: unreferenced static fns (calling shared static inline helpers) placed in source where the stripped fn would compile; one fn pools its double after its floats, so a double between float groups needs its own fn; verify by linking as Matching: DOL size identical and diffs only in known near-miss fns
