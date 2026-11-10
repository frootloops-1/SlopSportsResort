# volatile local keeps by-value struct param copy

- status: works
- tags: struct-param,volatile,frame
- scope: RPSportsCommon_unsplit

symptom: 38.8%: by-value struct copied to local optimized away into tail call
cause: dead local copy removed
fix: volatile Pt2 p = pos; and compute const char* name before inlined call
