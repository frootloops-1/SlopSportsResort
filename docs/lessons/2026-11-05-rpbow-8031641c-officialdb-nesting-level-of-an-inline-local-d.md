# RPBow_8031641C officialDb: nesting level of an inline local does not change its colouring order

- status: fails
- tags: regalloc,inline-level,RPBow_8031641C
- source: RPBow_8031641C round 3

symptom: officialDb (two defs) must colour after the getU32 seed/x temp and before the hoisted MULT/SHIFT
cause: unknown; inline-declared local (any nesting level 1-3) colours before db/x, return-value inline adds an mr, named local colours last
fix: none: XOff3 inline + hand-new db = 12 lines but wrong order; body accessor in kokeshi loops is also worse
