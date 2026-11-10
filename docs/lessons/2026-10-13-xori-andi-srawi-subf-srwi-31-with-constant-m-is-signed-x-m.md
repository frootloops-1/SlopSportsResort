# xori/andi./srawi/subf/srwi 31 with constant M is signed x < M

- status: works
- tags: compare,idiom,signed,xori
- scope: RPGol_802c16a4
- source: claude/rpgolscene-unsplit

symptom: xori r4,r3,M; andi. r0,r4,M; srawi r4,r4,1; subf r0,r0,r4; srwi r4,r0,31
cause: MWCC branchless signed less-than against a constant
fix: write plain f() < M (no & M); (f() & M) < M adds a leading andi.
