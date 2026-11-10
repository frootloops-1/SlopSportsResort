# Lowest-rank local: compute in static inline returning pointer; ConvertOffsToPtr not inlined

- status: works
- tags: regalloc,static-inline,return-value,forcebind
- scope: Pack/RPKernel/RPSysLayout

symptom: pContent got r26 not r21
cause: return value of inline gets lowest reg
fix: static inline GetAnimContent(pRes,tbl,idx) returning pointer; allocStringBuffer pane-param rank unfixed (decl order sets locals' relative rank only)
