# RPGol curve vtable fns (float,u16) are methods: this first

- status: works
- tags: abi,virtual
- scope: RPGol_802b5638
- source: fn_802B5808

symptom: r3/r4 swap
cause: declared as free fn(float,u16)
fix: declare (void* self, float x, u16 i)
