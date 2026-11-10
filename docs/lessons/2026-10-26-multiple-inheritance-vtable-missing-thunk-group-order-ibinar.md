# Multiple-inheritance vtable: missing thunk + group order = IBinary has 4 virtuals, GetVersion is own virtual declared first

- status: works
- tags: vtable,IBinary,thunk,eggLightTexture,multiple-inheritance
- scope: egg/gfxe/eggLightTexture
- source: lt-data-1026

symptom: LightTexture .data 76%: extra @44@GetVersion thunk, group-2 vtable entries in wrong order/count; 8 byte shift in DOL
cause: CW appends the class's own virtual entries after the secondary table in header declaration order; target secondary IBinary table has 4 thunks and GetVersion (no thunk) is the first own entry
fix: local IBinary copy (EGG_CORE_IBINARY_H) without pure GetVersion + declare GetVersion first and Size before Type in LightTexture; name vtable __vt__ with size 0x44 (4B pad excluded). .data 100, DOL only SetBinaryInner 4B off
