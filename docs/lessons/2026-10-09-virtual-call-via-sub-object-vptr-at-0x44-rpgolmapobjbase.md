# Virtual call via sub-object vptr at +0x44 (RPGolMapObjBase)

- status: works
- tags: golf,vtable,RPGolMapObjBase
- scope: RPGolMapObjBase
- source: haiku

symptom: lwz r12,0x44(r3); lwz r12,0x1c(r12) tail call; function-pointer view loads vptr into r5 (98.8%)
cause: vptr offset/reg needs a real class
fix: struct Base{u8 pad[0x44];}; struct Obj:Base{ 5 virtuals; virtual void X(s32);} ; slot=2 dtor slots+index; pass s32 flag!=0 not bool
