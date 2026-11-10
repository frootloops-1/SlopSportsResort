# RPBow_8031641C fn_80318EB0 officialDb: no source form numbers a pre-loop variable after the loop's getU32 return temp

- status: fails
- tags: RPBow_8031641C,regalloc,officialDb
- scope: RPBow_8031641C
- source: round 4

symptom: officialDb r24 (named) vs retail r17; retail needs its @id between x (getU32 return @1957) and the LICM temps (MULT @2060)
cause: Inline locals (any nesting) and ternary/return temps are numbered in source order before x; named locals are below every @
fix: none: tried XOff local nesting 1-7 (16 lines), ternary / return temp (13, extra mr from new-temp coalescing), x as XSwap/XSwapC inline local (no change), db hand-new combos (12 best), NULL-init (25). Parked at harness 23
