# SpMdlSetD: local pragmas, partial re-reads and placement-new steering all fail

- status: fails
- tags: register,pragma,steering,parked
- scope: RPSportsCommon/RPSports_801f1d4c
- source: claude/sp801f1-1104f 051400c75

symptom: mgr/anm r24 vs retail r25 after 6 passes
cause: Allocator picks lowest used non-conflicting reg; named mgr would need to conflict with both loop-1 IVs (r23,r24) before the loop starts; window temps are live across loop 1; CSE temps >=7070. Pragma push/pop in this TU also dropped fn_801F63CC to 0 while present
fix: open: parked; needs a compiler-pass insight
