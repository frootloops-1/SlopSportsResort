# Unsplit blob: split finished TUs out so sdata2 literal relocs match

- status: works
- tags: unsplit,sdata2,split,literal,reloc
- scope: RPGolScene_unsplit
- source: claude/rpgolscene-unsplit

symptom: fn in a multi-TU _unsplit object stuck <100 with only lfs @N@sda21 vs lbl_ arg mismatches; values identical
cause: objdiff matches pooled literals by offset in the object's .sdata2; the unsplit's pool starts far earlier, and one-TU compile would also dedupe literals across original TUs
fix: find TU boundaries (one vtable per class in .data in text order; per-TU sdata2 ranges; a duplicate literal value = new TU; sdata2 padded to 8 per TU), carve a new splits.txt object (e.g. RPGol_802c7384.cpp) and shrink the unsplit ranges; trailing pad symbols size 8->4
