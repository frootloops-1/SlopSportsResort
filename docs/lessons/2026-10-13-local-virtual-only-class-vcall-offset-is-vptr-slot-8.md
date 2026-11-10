# Local virtual-only class vcall offset is vptr slot +8

- status: works
- tags: vcall,vtable,offset
- scope: RPSportsCommon_unsplit

symptom: 99.8-99.9% on vcall fns, lwz offset 8 too large
cause: local class with only virtuals and no dtor starts slots at 0x8
fix: use method index (O-8)/4 for original offset O (v22 for 0x60, v5 for 0x1C)
