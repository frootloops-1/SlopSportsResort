# resort: EGG::ModelEx is 0x10 with no vtable (ScnObj* 0x0, type 0x4, u16 flag 0x8, BV 0xC)

- status: works
- tags: resort,egg,modelex,rpgrpmodel,layout

symptom: every RPGrpModel accessor off by field order
cause: ogws ModelEx has a vtable and type first; Resort ctor 0x801B3DC4 stores ScnObj at 0x0 and no vptr
fix: Header changed: +17 exact across the RPGrpModel family
