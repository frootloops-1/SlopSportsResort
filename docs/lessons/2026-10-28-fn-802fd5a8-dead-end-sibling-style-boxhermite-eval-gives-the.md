# fn_802FD5A8 dead end: sibling-style BoxHermite eval gives the target's relative colouring but colours the CSE'd constants first (+2 shift, 96.0)

- status: fails
- tags: regalloc,fpr
- scope: RPBox_802fd228 fn_802FD5A8
- source: FPR batch 2 2026-10-28

symptom: 97.1 residue inside the inlined Hermite eval
cause: reordering initialised decls changes the nested-eval schedule; an invented BoxFrameDt() helper gave 97.2 (+0.1) and was dropped to avoid a marker
fix: none: uninitialised decls up front (3 orders), reordered eval, named one + explicit lerp expressions (96.0)
