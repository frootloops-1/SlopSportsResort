# fn_801E2970 now a pure r6/r7 volatile swap (99.6%)

- status: fails
- tags: volatile-swap,regsearch,ternary
- source: RPSports_801DF984

symptom: page-0 block: orig zero=r6, mulli offset=r7; ours swapped; 22 diff lines
cause: volatile colouring order of zero vs offset vreg; unresolved
fix: tried decl order, literal 0, index=typeVal (62), no index (30), type decl above getChannel (24), initPage inline helper (133), regsearch generic 7min no change
