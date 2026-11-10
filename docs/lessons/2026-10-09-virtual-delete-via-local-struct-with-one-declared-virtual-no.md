# Virtual delete via local struct with one declared virtual, not fn-pointer cast

- status: works
- tags: virtual,vtable,dtor,r12
- scope: RPGolMain

symptom: (*(Fn**)p)[2](p,1) emits lwz r5 instead of lwz r12 (99.4%)
cause: function-pointer cast uses a non-r12 temp
fix: local struct VirtualObj { virtual void* deleting(s32); } gives lwz r12,0 / lwz r12,8 / mtctr
