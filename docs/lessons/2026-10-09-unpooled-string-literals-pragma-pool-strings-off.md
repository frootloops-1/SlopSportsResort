# Unpooled string literals: #pragma pool_strings off

- status: works
- tags: msl,strings,sdata2,rodata
- scope: MSL_C objects with non-pooled strings
- source: claude/msl-data 2026-10-09

symptom: Original object has each string as its own symbol (short ones in .sdata2, longer in .rodata); ours has one @stringBase0 pool in .rodata
cause: cflags_runtime passes -str reuse,pool,readonly; no later -str option (nopool, reuse only) turns pooling off, and dropping readonly puts strings in .data
fix: Put '#pragma pool_strings off' at the top of the source file (src/MSL/locale.c); small strings then land in .sdata2 like the original
