# ctor count 10 lands in r4 vs orig r0 (97.2)

- status: open
- tags: regalloc,ctor
- scope: RPGol_802b4f2c
- source: fn_802B54A0

symptom: li r4,10 vs li r0,10; addi r0,r3,0x24 scheduling
cause: unknown
fix: dead ends: chained, u32, s32* index, s32 vtable stores, vt local (97.1); try permuter
