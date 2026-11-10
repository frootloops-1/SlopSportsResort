# resort: carving RP files: vtable slot dumps, shared sdata2 constants and CreateInstance (new + store to spInstance) give file bounds

- status: works
- tags: resort,carve,split,M4
- scope: resort
- source: RP batch 4 (2026-11-09)

symptom: name-matched Pack splits short by CreateInstance / thunk tails; unk sinit units belong to named files
cause: file ends at the function storing spInstance; an __sinit sharing .sdata2 constants with a file is that file's; a 4-8 byte @thunk after __sinit stays with it
fix: 31 files carved, 23 ogws sources compiled unchanged (+10 exact); M4 84% -> 96%
