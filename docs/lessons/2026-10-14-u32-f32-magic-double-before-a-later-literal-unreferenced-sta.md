# u32->f32 magic double before a later literal: unreferenced static f32 fn(u32) last in source

- status: works
- tags: sdata2,pool-order
- scope: RPGol_802b8568
- source: fn_802B859C

symptom: identical asm 99.7, double pooled after 5.0f
cause: creation order
fix: static f32 GolPoolOrder(u32 x){ return (f32)x; } at end of file (adds a 0x24 local fn to .o; linker strips)
