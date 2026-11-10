# RPBow 803CA858-940 per-owner re-split: owners define hand vtables at file end, jump table renamed to compiler @N

- status: works
- tags: data,splits,rpbow,jumptable,vtable
- scope: Pack/RPSports/RPBowScene/RPBow_803433E4
- source: claude/bow-803433E4-1105

symptom: 803433E4 code 100 but its switch table sat in 803381DC's lumped .data; previous re-split attempt regressed Matching neighbours' .data
cause: owners did not define the moved tables; dtk name jumptable_X does not pair with the compiler's local @N; explicit gap_ symbol for the 8-align pad
fix: splits.txt: shrink lumped split, give each owner its range (monotone); each owner defines its table (hand void* vtable at file end in extern C, R17; float table as real definition replacing extern); symbols.txt rename jumptable_803CA858 -> @1897 (nm of our .o) and delete gap_08 (MWCC emits the 8-align pad before the next array). All 6 units .data 100, FLIP-OK
