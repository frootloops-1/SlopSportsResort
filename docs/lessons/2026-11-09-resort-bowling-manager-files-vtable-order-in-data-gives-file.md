# resort: Bowling manager files: vtable order in .data gives file order; X blr before Update, 0x40 dtor last

- status: works
- tags: resort,splits,bowling,vtable
- scope: resort
- source: bowling-splits

symptom: carving Bowling files out of unk/ blobs
cause: manager vtables [0,0,dtor,v2,Update,X,base..]; X is a blr emitted just before Update; dtor is the file's last function (not a start marker)
fix: use vtables in .data 0x806DE958-0x806DED20 (same order as the files), .ctors sinits and .sdata2 pool continuity to set boundaries
