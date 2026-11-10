# fn_802B51D0 ball/pin saved-reg swap (99.8)

- status: open
- tags: regalloc
- scope: RPGol_802b4f2c
- source: fn_802B51D0

symptom: orig ball r28, pin r26; ours swapped
cause: unknown
fix: dead ends: all decl-order permutations of cfg/pin/pos/ball/ok/tgt, IsStateOk inline on/off, tail rewrites; try permuter
