# Ctor copying 0x50-byte local aggregates: nested struct member gives unrolled copy

- status: works
- tags: mwcc,struct-copy,rodata,RPBox
- scope: RPBox_802e9774

symptom: orig stack->member copy unrolled lwz/stw; flat f32[20] POD gave lwzu ctr loops (40%)
cause: MWCC copies nested-member structs member by member
fix: struct {f32 a[1]; V3 b; f32 v[16];}; scalar float member as f32 a[1] to get lwz/stw (99.2%)
