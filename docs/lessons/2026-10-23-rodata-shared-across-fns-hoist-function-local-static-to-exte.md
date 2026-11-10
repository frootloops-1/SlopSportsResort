# Rodata shared across fns: hoist function-local static to extern C const named lbl_X

- status: works
- tags: rodata,static,relocation
- source: RPBox_802cf93c 2026-10-23

symptom: two fns reference the same rodata (lbl_8038FBD4); local static gives a private symbol name and reloc diff
cause: function-local statics can't be shared; objdiff matches reloc names
fix: extern "C" { extern const T lbl_X; const T lbl_X = {...}; } at file scope before first user
