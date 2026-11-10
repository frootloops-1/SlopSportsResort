# RP_DEBUG_STUB_1 deleting dtor: extern C fn(void*,s32) + void* vtable[3]; double beq from nested if(self)

- status: works
- tags: debug_stub,dtor,vtable,beq
- scope: RPGolMain

symptom: deleting dtor of RP_DEBUG_STUB_1 subclass (fn_8028E760) needs two beq
cause: original has redundant null check
fix: wrap base __dt__ call in a nested redundant if(self); manual vtable array as in RP_DEBUG_STUB_2.cpp
