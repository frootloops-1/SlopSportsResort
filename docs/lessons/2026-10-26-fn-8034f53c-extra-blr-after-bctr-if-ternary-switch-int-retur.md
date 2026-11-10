# fn_8034F53C extra blr after bctr: if/ternary/switch/int-return/local-ptr forms all keep exit blr

- status: fails
- tags: RPBow_8034E974,blr,virtual-tail-call,branch-shape
- scope: RPBow_8034E974

symptom: 13 instrs vs target 12; trailing blr after final bctr (91.7%)
cause: MWCC emits an exit block after the virtual tail call whenever a true-branch return exists; no-branch tail call has no blr
fix: dead end (worker, haiku): early return, ternary, switch, u8/int return, local BowSlot* all unchanged; reversed branch gives wrong layout. Needs a different lever (unknown)
