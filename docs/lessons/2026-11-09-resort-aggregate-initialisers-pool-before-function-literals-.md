# resort: aggregate initialisers pool before function literals; collapse lbl_ strings to one @stringBase0

- status: works
- tags: resort,rodata,sdata,string-pool
- scope: resort
- source: pools

symptom: layout/singleton files 97-99.x with identical asm
cause: file-scope const char* tables (.data) and pointers (.sdata) pool first in declaration order; objdiff needs the pool as one symbol
fix: declare the name tables at file scope in order; in symbols.txt replace the per-string lbl_ entries with one @stringBase0 (scope:local, data:string_table) of the unpadded size; check splits for truncated .rodata ends
