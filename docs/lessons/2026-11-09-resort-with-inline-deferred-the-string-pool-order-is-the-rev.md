# resort: with -inline deferred the string pool order is the reverse of source function order

- status: works
- tags: resort,rodata,string-pool,inline
- scope: resort
- source: pools

symptom: singleton create 97.5%: class-name string at the wrong pool offset
cause: strings pool in emission order; deferred inlining emits the last-defined function first
fix: keep each file in descending address order; insert new functions next to their address neighbour (tools/reorder_fn.py <fn> after <higher fn>); write the real users of earlier strings rather than seeding
