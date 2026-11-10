# fn_80201240: volatile SpV3 local pins store order y,x,z

- status: open
- tags: volatile,r17,store-order
- scope: RPSports_80201240

symptom: stores emitted z,x,y vs target y,x,z; const lfs hoisted above stw r0
cause: scheduler
fix: volatile SpV3 pos gives store order (94.6->94.7, R17); const-load hoist unsolved; direct member stores/const ptr/swapped operands worse
