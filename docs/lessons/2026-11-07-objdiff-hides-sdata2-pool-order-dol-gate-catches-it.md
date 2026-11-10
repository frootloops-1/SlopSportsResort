# objdiff hides .sdata2 pool order; DOL gate catches it

- status: works
- tags: sdata2,pool,objdiff,flip
- scope: RPBoxScene
- source: RPBox 2026-11-07

symptom: unit_cmp 100% everywhere but flip_gate shows diffs in .sdata2 and every lfs site
cause: objdiff pairs pool literals by value; after asm conversion the parse-time literal order changes
fix: asm2cw --seed helper placed after the unit's named .sdata2 definitions; always run the DOL gate
