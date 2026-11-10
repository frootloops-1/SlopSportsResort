# RPGolConfig score loops close via inline helper and indexed stores

- status: works
- tags: RPGolConfig,regalloc,inline,loop
- scope: fn_8029D4BC
- source: docs/tasks/RPGolConfig.md

symptom: 99.37956% with 137 identical instruction shapes but different saved GPR roles
cause: Walked row pointer and caller locals colored in a different order
fix: Move the record lookup plus score-clear/load loops into static inline GolLoadScores(m). Replace *++p with m->score[i][j]. Whole function now matches 548 raw bytes and all 17 relocations; preserve existing callees out of line and source emission order. Six compilers tie.
