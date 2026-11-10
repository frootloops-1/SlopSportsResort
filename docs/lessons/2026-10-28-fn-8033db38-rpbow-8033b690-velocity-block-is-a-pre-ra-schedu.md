# fn_8033DB38 (RPBow_8033B690): velocity block is a pre-RA schedule wall, five colouring lever families do not touch it

- status: fails
- tags: regalloc,fpr,schedule
- scope: RPBow_8033B690 fn_8033DB38
- source: FPR experiment 2026-10-28

symptom: velI-first FPR order wall at 96.0%
cause: target first 19 insns equal ours with I/J slots mirrored (velI = cpI - oI first), but velI-first source interleaves loads differently (n load later, second ps_sub f5 vs f6); velI/velJ are memory VEC3 so there is no named-vs-temp choice
fix: none: rel moved after dots (identical), tI/tJ named copies (94.2), inline BowSubTo (95.9/94.2), oJ/cpJ decl swaps (94.2), vi-before-vj dot swap (93.1). Park; treat as scheduler wall
