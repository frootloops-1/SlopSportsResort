# pool_data off scoped to the function that stores same-TU vtables

- status: works
- tags: data,vtable,pragma,ctor
- scope: Pack/RPSports/RPTnsScene/RPTns_802338a4

symptom: ctor fn_80234488 100% until the TU's own manual void* vtable arrays were defined; then 1252!=1364 bytes, one lis/addi section base + addi offsets instead of lis/addi per vtable
cause: MWCC pools same-TU .data objects behind a base register; codegen is deferred so the pragma state at the function definition matters, not at the data definitions
fix: #pragma pool_data off / reset around only that function. Around the data defs: no effect. File-level: breaks .sdata2 float loads elsewhere (li base + lfs off)
