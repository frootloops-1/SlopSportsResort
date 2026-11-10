# objdiff [.data-0] <100% from weak nw4r vtables/dtors is not fixable in source; fix symbol sizes in symbols.txt first

- status: works
- tags: objdiff,data,weak,vtable,symbols.txt,RPGrpModelImplement
- scope: RPGrpModelImplement

symptom: RPGrpModelImplement .data 99.6% and .sbss 50%; [.data-0] stays 89% after symbols fixed (ours 304 bytes vs target 248)
cause: symbols.txt sizes included alignment padding (vtable 0xF8 vs real 0xF4; sbss flag 0x8 vs 0x1). Remaining [.data-0] gap is two unreferenced weak vtables (IScnObjCallback 0x20, ICalcWorldCallback 0x18) MWCC emits in our .o; the original link kept the first copy in another TU. Already-Matching ModelScene (75%) and Renderer (91%) show the same artifact.
fix: Set real symbol sizes (0xF4, 0x1); dtk adds hidden gap_* padding symbols. Accept [.data-0]<100 when the surplus is only weak dup vtables; DOL check is authoritative.
