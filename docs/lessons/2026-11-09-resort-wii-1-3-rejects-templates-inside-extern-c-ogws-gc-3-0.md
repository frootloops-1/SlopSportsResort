# resort: Wii/1.3 rejects templates inside extern "C" (ogws GC/3.0a5.2 ports)

- status: works
- tags: resort,porting,compiler
- scope: resort
- source: bowling-splits

symptom: illegal template linkage when porting ogws Bowling files
cause: GC/3.0a5.2 accepts templates in extern C blocks; Wii/1.3 does not
fix: close the extern "C" block around templates. Also: ogws files that share one .sdata2 pool in Resort (NpcManager + RPBow_80330FE8) are one TU there
