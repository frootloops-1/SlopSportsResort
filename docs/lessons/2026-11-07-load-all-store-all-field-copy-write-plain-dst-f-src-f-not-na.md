# Load-all/store-all field copy: write plain dst->f = src->f, not named temps

- status: works
- tags: mwcc,scheduling,regalloc,copy,golball
- scope: RPGolMapObjBall fn_8029A3FC
- source: claude/golball-c-1107 514dc15fd

symptom: Block of loads then block of stores (src->dst field copy); named-temp C has the first-stored value loaded last into r0 and GPR colors shifted
cause: MWCC forwards a single-use local whose load has no intervening store (always the first-stored one) to its store; plain field assignments are expression temps colored in reverse load order and the scheduler hoists the loads itself
fix: Write dst->x = src->x; per field in source order (fn_8029A3FC 38 -> 0 diffs, also tail byte pair). Element loop needed its own static inline to get index/offset r11/r12
