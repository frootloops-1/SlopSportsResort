# ef_animcurve U8 colour order: keySize before pKeys and in-place found-key cursor

- status: works
- tags: ef_animcurve,U8,colouring,cursor
- scope: nw4r/ef/ef_animcurve
- source: claude/ac-u82-1029 opus

symptom: U8 prologue header temps r0/r8/r6 vs target r8/r6/r0; found-key key r3 + values r4 vs target shared r4
cause: mwcc_dbg: non-callee temps are coloured in DESCENDING vreg order, lowest free reg; computing (count+13) before pKeys makes it the oldest temp so it is coloured last. Found key: a separate key var gets r3 first; one in-place web (values=keys; values+=idx*keySize; flag=values[2]; values+=12) shares r4 (initializer 'values = keys + idx*keySize' gets a frontend temp+mr that copy-prop splits off, so the += form is needed)
fix: keySize=(count+13)&~1 moved above pKeys: 99.54622/38 -> 99.57143/26. In-place found cursor: 99.58403/20. No markers.
