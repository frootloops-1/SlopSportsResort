# Lone 4-byte .sbss var: shrink symbol to real size

- status: works
- tags: splits,sbss,symbols
- scope: objects with one 4-byte .sbss/.sdata var
- source: claude/msl-data 2026-10-09

symptom: objdiff shows .sbss 8 vs 4, the data symbol at 50%, report shows 0 matched data
cause: dtk sizes a symbol to the next symbol, so a 4-byte int sits in an 8-byte slot (alignment padding) while our compiled .sbss is 4
fix: Set the symbol size to 0x4 in symbols.txt (as for nw4r typeInfo); the section stays 8 on the target side, expected for Matching objects
