# Dead expression statement forces literal pool order

- status: works
- tags: sdata2,literal-order
- scope: RPGolScene
- source: claude/rpgol-family

symptom: 99.6-99.7% reloc mismatch: .sdata2 pool order differs
cause: MWCC pools literals in IR creation order
fix: Put a dead '0.5f;' statement at the top of the function; a named local float changes regalloc instead (fn_802AF98C/AFA5C/B5CFC/B5DCC)
