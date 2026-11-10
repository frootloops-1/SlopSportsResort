# RPBow lumped .data split: assign vtables/jump tables by function-pointer text ranges, monotone in link order

- status: works
- tags: splits,data,vtable,rpbow,jumptable
- scope: RPBow_80313028

symptom: RPBow_80313028 .data stuck at 41%: its split range 0x803CA1B8-0x803CA688 also held other units' vtables and a jump table
cause: lumped split; later units' data sat in the first unit's range
fix: Read each object's .4byte function pointers in the lumped asm: a vtable/jumptable belongs to the unit whose .text range holds its first (dtor/key) slot or jump target, and ranges must stay monotone in link order. Where the owner is a Matching unit with no .data of its own (8031C388, 8031EFE4), give the range to the next NonMatching unit in link order (80320EFC): identical layout, DOL 0. Result: .data 100 and sbss untouched. sbss (all RPBow units lumped in 0x804BF998-0x804BFA10) has no pointer evidence for ownership and was left alone.
