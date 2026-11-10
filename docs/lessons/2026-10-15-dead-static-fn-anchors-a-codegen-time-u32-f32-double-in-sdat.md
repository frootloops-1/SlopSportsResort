# Dead static fn anchors a codegen-time u32->f32 double in .sdata2

- status: works
- tags: sdata2,pool,anchor,double
- scope: mwcc
- source: RPTns_802390b0

symptom: 0x4330000000000000 pooled after a later fn's floats
cause: pool order = generation order (reverse source); the int->float double is created when the converting fn is generated
fix: static f32 TnsU8ToF32(u8 c){return c;} placed in source between the fns bracketing the target slot; linker strips the local fn
