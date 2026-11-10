# resort: size += accumulation in nw4r CalcMemorySize regresses EffectMgr

- status: fails
- tags: resort,rp,data

symptom: createMemoryManager 99.6, createSlowSystem 98.9 register residue
cause: inline in ef_memorymanagerimpl.h; retail sums size+roundup into a temp
fix: none yet; += variant drops both to ~95
