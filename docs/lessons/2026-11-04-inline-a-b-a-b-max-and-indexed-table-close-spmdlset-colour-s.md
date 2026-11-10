# Inline a>b?a:b max and indexed table close SpMdlSet colour swap

- status: works
- tags: register,max,induction,table
- scope: RPSportsCommon/RPSports_801f1d4c
- source: claude/sp801f1-1104c ca79071d0

symptom: tbl r24 vs idx*4 r25
cause: if (x>n) n=x; makes a frontend temp for x that pushes the induction temp early; walking named pointer vs indexed read changes IV numbering
fix: static inline max a>b?a:b (nw4r::ut::Max flips the compare); read tbl[j] instead of walking pointer
