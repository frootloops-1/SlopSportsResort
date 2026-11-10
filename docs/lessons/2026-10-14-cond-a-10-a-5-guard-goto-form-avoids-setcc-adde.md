# cond ? a>=10 : a>=5 guard: goto form avoids setcc/adde

- status: works
- tags: branch,goto,bool
- scope: RPTns_80230904
- source: sonnet worker 2026-10-14

symptom: setcc/adde or li/cmpwi for a mode-dependent threshold guard
cause: orig branch layout bge body / b end / blt end
fix: if(m==0){ if(x>=10) goto body; goto done; } else if(x<5) goto done; body: ... done:
