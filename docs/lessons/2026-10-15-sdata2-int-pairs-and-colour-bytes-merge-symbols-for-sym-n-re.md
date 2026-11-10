# sdata2 int pairs and colour bytes: merge symbols for SYM+N relocs

- status: works
- tags: sdata2,symbols,reloc
- scope: RPTns
- source: RPTns_80235cd0

symptom: 100% instructions but reloc names SYM+4 / SYM+1..3 differ
cause: symbols.txt splits 8-byte pairs and 4-byte colours into 4/1-byte labels
fix: merge into size 0x8 / 0x4 objects in symbols.txt (RPTns_80235cd0: 3 fns became exact)
