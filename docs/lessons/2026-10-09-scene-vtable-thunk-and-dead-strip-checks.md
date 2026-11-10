# Scene vtable thunk and dead-strip checks

- status: works
- tags: vtable,inline deferred,dead strip,RPGolScene
- scope: RPGolScene

symptom: this-adjust thunk (subi r3,0x24; b dtor) got inlined into a full copy; link shrank by 0x360 with all objdiff 100%
cause: inliner folds thunk; vtable listing only 25 of 32 words left callees unreferenced so they were dead-stripped
fix: #pragma dont_inline on around the dtor body (3 nested if(scene) reproduces the triple beq); fill every vtable word incl. trailing ones - no force_active needed; pass state to callee as arg to get lwz r3 instead of r0
