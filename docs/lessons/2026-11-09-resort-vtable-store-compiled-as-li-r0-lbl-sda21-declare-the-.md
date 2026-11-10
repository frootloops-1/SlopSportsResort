# resort: vtable store compiled as li r0,lbl@sda21 -> declare the vtable extern void* lbl[]

- status: works
- tags: resort,vtable,sda,ctor
- scope: resort
- source: jsk-wkb

symptom: ctor storing a vtable pointer uses an r13-relative address instead of lis/addi
cause: a 4-byte extern void* lbl is small-data addressed
fix: declare it as an unknown-size array: extern void* lbl[]; *(void**)(p+N) = lbl; base-ctor-plus-vtable ctors then match
