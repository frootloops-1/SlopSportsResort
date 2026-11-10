# resort: Wii Sports all-in-one sum in CalcMemorySize folds RoundUp

- status: fails
- tags: resort,rp

symptom: createSlowSystem drops to 90.6
cause: constant folding
fix: separate MemInfo header term gives the retail temp; remaining is register colouring (99.6/98.9)
