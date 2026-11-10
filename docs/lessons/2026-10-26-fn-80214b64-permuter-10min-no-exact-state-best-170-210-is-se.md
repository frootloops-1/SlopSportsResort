# fn_80214B64 permuter 10min: no exact state, best 170/210 is semantically broken

- status: fails
- tags: dead-end,permuter,ctor
- scope: RPTns_80214480
- source: claude

symptom: li r4,6 + hoisted addi r0 (98.32%)
cause: unknown register-coloring order; 8.5k iterations, 1298 stand-in errors (KeyError on SoundHandle ctor in __construct_array)
fix: best candidate 170 stored count via aliased temp, writing the vtable to actor+0x40 instead of +0x3C: invalid, not applied. Source unchanged.
