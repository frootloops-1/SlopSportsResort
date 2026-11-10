# resort: renaming an lbl_ referenced by a Matching unit's extern placeholder breaks the link

- status: works
- tags: resort,symbols,rename,extern
- scope: resort
- source: RP batch 4 (2026-11-09)

symptom: after renaming lbl_806F4D10 -> spInstance__14RPSysEffectMgr the flipped link reports undefined symbol in RPGrpDrawPathManager
cause: Matching units that declare extern "C" lbl_/fn_ placeholders bind by the old name
fix: grep src for the old name before renaming; switch that unit to the real accessor (RPSysEffectMgr::instance())
