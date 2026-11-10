# fn_80313028: lwz name vs lfs f1 order fixed by reordering the guessed prototype args (f32,f32,const char*,f32,...)

- status: works
- tags: scheduling,prototype,arg-order,RPBow
- scope: RPBow_80313028

symptom: name lwz r3 scheduled before lfs f1 (6 diff lines); direct arg, getters, locals, f32 fy locals all flat
cause: ABI-equivalent prototype arg order changes pre-scheduler evaluation order; floats and ints use separate registers so the true order is unrecoverable from asm
fix: declare fn_801C38B8(f32, f32, const char*, f32, u32, bool) and reorder call args: fn_80313028 99.7 -> 100 (MATCH-PENDING row 143). General: when a call's int arg loads schedule against float const loads, try moving that param position in the prototype
