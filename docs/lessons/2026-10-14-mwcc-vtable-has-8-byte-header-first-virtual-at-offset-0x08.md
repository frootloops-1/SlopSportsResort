# MWCC vtable has 8-byte header: first virtual at offset 0x08

- status: works
- tags: vtable,virtual,thunk
- source: RPBsb_8027383c

symptom: bctr tail jump called slot 0x44 instead of 0x3C
cause: view slots named from 0 but vtable starts with 8-byte header
fix: name view virtuals vf08,vf0C,... so name equals vtable offset; plain self->vfN() already emits frameless lwz/lwz/mtctr/bctr
