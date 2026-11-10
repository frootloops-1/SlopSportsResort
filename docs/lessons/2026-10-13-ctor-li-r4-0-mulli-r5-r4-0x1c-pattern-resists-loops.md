# ctor li r4,0; mulli r5,r4,0x1c pattern resists loops

- status: fails
- tags: mulli,constant-fold,ctor,loop
- scope: Pack/RPKernel/RPSysPauseMenu

symptom: ctor 74.6%: original multiplies index 0 by 0x1c per entry
cause: all loop/inline/pointer variants constant-fold
fix: dead ends: int/u8 for, do-while, inner j loop, explicit stores, inline clearEntry(0/1/2), raw ptr arithmetic; try permuter or phi/condition-derived index
