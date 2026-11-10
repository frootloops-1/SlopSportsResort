# resort: placeholder virtual structs reproduce vtable calls; raw function-pointer casts don't

- status: works
- tags: resort,virtual,first-pass
- scope: resort
- source: basketball

symptom: vtable tail call uses r4 scratch or swapped lwz order (98%)
cause: casting through a vtable array changes the load order/scratch register (orig uses r12)
fix: struct Unk_VtAtNN { u8 pad[NN]; virtual void vf8(); virtual void vfC(); }; p->vfC(); with pad = vptr offset. Struct-copy lfs/lfs/stfs/stfs with descending regs = assign a {f32 x,y[,z]} struct
