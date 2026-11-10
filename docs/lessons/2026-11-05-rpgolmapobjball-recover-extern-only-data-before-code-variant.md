# RPGolMapObjBall: recover extern-only data before code variants

- status: works
- tags: data,symbols,sdata2,RPGolMapObjBall
- scope: Pack/RPSports/RPGolScene/RPGolMapObjBall
- source: codex-golball-1105

symptom: 33/54 functions exact, 98.89% code, data sections 0-21.79%; many near-100 functions have data-reference differences.
cause: Source defined almost no owned data. Target merged 0/1 float labels into @13725 and included alignment padding in two globals.
fix: Define original string pool, tuning constants, BSS arrays, pointers and relocation-backed vtables; split @13725 into lbl_804C4030/4034, trim flag/pointer symbols to 1/4 bytes, use explicit_zero_data for zero sdata flag. 45/54 exact, all six data/BSS sections 100%, no regressions; still NonMatching.
