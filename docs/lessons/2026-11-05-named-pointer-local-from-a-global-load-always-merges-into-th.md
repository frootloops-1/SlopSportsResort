# Named pointer local from a global load always merges into the load temp (fn_80338760 SE manager)

- status: fails
- tags: colouring,named-local,pointer,merge,fn_80338760
- scope: Pack/RPSports/RPBowScene/RPBow_803381DC

symptom: inline param pSnd coloured r20, retail r19 (after triBall)
cause: the pointer local merges into its load temp whatever its declaration (const, ref, void* cast, top-declared, manual inline with goto)
fix: dead: all those spellings unchanged (6 lines). Enum lever does not apply to pointers
