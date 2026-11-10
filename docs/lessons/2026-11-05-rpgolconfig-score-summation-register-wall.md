# RPGolConfig score summation register wall

- status: fails
- tags: RPGolConfig,regalloc,types,inline,R17
- scope: fn_8029CCBC
- source: docs/marker-ledger.md

symptom: 82 identical instructions but register roles differ at 98.4756%
cause: Named locals and inline GolBase expansions color differently; six compiler versions tie
fix: Thirty type/declaration/helper probes failed; const main pointer reduced normalized differences 20 to 17. Native symbolic assembly matches all 328 bytes and three relocations, annotated R17 row 224, prior C++ retained.
