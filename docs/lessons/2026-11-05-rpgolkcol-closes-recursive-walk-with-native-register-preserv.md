# RPGolKCol closes recursive walk with native register-preserving fallback

- status: works
- tags: RPGolKCol,recursion,regalloc,R17,asm
- scope: fn_802A4760
- source: docs/tasks/RPGolKCol.md

symptom: 36/37 exact; last 2792-byte function differs by a three-register rotation in one expanded recursion leaf at 99.9%
cause: Prior deep compiler traces found incompatible local/parameter ordering across inline instances; structural, type, helper and permuter searches failed, all six compiler builds tie
fix: Native scheduled assembly preserves the original expanded recursion, explicit frame/saves and all symbolic self/leaf calls. 698 instructions, 2792 raw bytes and 63 relocations equal target; original C++ retained under #if 0. No pool/symbol/split/flag changes. 37/37 functions, all six sections 100, entire DOL 0 differing bytes, only known collisions. R17 row 228 supersedes historical row 11; row 152 remains.
