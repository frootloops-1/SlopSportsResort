# fn_8021013C closed: dead/read copy pair created at helper expansion via v.set(SpPassPos(call())) and index as inline param

- status: works
- tags: stack,temps,inline-param,colour,rpsports,8020f530
- source: sp8020f-1104

symptom: effect copies at frame bottom (0x10/0x08) vs retail 0x40/0x38+0x30/0x28; cur in r28 vs r29
cause: copies created by a nested inline (ctor->set) are deferred to a late pass; params of inlines called directly from the auto-inlined helper are created at its expansion; the read copy is the last one
fix: default-construct SpVec3f, v.set(SpPassPos(fn_801D01F0(...)), -120); decide-button code in inlines taking cur as param; unit flipped FLIP-OK
