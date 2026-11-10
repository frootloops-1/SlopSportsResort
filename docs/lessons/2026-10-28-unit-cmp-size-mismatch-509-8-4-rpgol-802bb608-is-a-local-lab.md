# unit_cmp SIZE-MISMATCH '@509 8!=4' (RPGol_802bb608) is a local-label numbering artifact, not a symbols.txt error

- status: works
- tags: tooling,symbols
- scope: RPGol_802bb608
- source: Gol units 2026-10-28

symptom: unit_cmp reported @509 8!=4 for a unit whose code matched
cause: target @509 is the 8-byte double 0x4330000080000000 at .sdata2 0x804C4A70 (symbols.txt size 0x8 correct); our compiler-numbered labels were 8 higher so our @509 was a 4-byte float (target @501); unit_cmp matches by name
fix: check the label offset before touching symbols.txt: a constant offset between our @N and the target's means extra/missing compiler-numbered statics earlier in the TU (here: extra inline or literal), and the mismatch disappears when the offset shifts. Bytes were identical by position
