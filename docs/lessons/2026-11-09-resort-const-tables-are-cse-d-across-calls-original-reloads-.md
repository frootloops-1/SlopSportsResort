# resort: const tables are CSE'd across calls; original reloads table[idx] after each call

- status: open
- tags: resort,rodata,volatile,MATCH-PENDING
- scope: resort
- source: rp9-renderer

symptom: fn_80254AE8 reloads table[idx] after each call while tables stay in .rodata
cause: const/extern const/file-scope/inline-static tables are CSE'd; only non-const (.data) or volatile reload
fix: open: static const volatile used as R17 marker (ledger #4); look for the authentic spelling
