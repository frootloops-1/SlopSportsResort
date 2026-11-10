# fn_8022F318 inlined-ctor result r29 vs r27: obj decl placement flat

- status: fails
- tags: regalloc,forecast,fn_8022F318,RPTns
- scope: fn_8022F318

symptom: obj (TnsMoveEnt result) shares reg with hit (r29) in ours but with pos (r27) in target
cause: obj is an inline-return @ var coloured before named pos; declaration scope of named obj does not matter
fix: dead ends: obj declared at use inside else-block (bit-identical), obj0 copy local (bit-identical). Diagnoser lever 9 irrelevant. Parked at 99.73.
