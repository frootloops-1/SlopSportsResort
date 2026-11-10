# LCG seed update: separate store then reread global, not chained assign

- status: works
- tags: regalloc,rand,global,assignment
- scope: Pack/RPUtility/RPUtlMath
- source: claude nearmiss 2026-10-15

symptom: fn_801BEBC0 98.7%: r3/r4 swapped for mullw result vs RANDF_MAX load
cause: u32 seed; value = MAX & ((seed = sSeed*MULT+1) >> SHIFT); sSeed = seed; gives other vreg order
fix: sSeed = sSeed*MULT+1; u16 value = MAX & (sSeed >> SHIFT); (same shape as sibling fn_801BEB1C) -> 100%
