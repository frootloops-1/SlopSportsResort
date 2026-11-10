# Declaration order of locals fixes callee-saved reg permutations

- status: works
- tags: regalloc,declaration-order
- scope: Pack/RPSports/RPSportsCommon/RPSysNunchukCheckScene/LoadResource,fn_801E3A5C

symptom: all instructions equal but r24-r31 assignments permuted (LoadResource 97.9%, 3A5C 99.7%)
cause: MWCC colouring depends on declaration order; one u16 i reused across loops also changes webs
fix: brute-force permutations of top-of-function declarations with a variant script (LoadResource: pCommonRes, pArchive, pLytArc, u16 i, pCommonMsg -> 100; 3A5C: pName before num -> 99.99)
