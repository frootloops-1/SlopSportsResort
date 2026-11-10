# resort: RPGrpModel layout differs from ogws (ModelEx 0x44, vtable 0x48, callback 0x2C, reverse culling 0x10)

- status: works
- tags: resort,RP,layout,RPGrpModel
- source: rp-graphics-layouts worker 2026-11-09

symptom: RPGrpModel users off by 4 (lwz 0x44 vs 0x40)
cause: Resort RPGrpModel members re-laid out
fix: ctor 0x8024E46C and Create*/Entry methods 0x8024E054-0x8024E3DC give the offsets (see RPGrpModel.h); raised all RPGrpModelImplement functions, finished RPGrpModelBoundingInfo
