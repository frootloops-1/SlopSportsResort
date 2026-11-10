# resort: .sdata2 local static arrays come before float constants; a string pool needs one @stringBase0 label

- status: works
- tags: resort,split,sdata2,string-pool
- scope: resort
- source: RP batch 5 (2026-11-09)

symptom: file start unclear; data tables pointing into strings miss
cause: .sdata2 puts function-local static arrays in source order before floats; tables only pair once the pool's labels are merged
fix: use the local-static block to find a file's first function; replace pool labels with @stringBase0 (scope:local data:string_table)
