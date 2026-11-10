# resort: RPSysSaveDataMgr is a smaller Resort class (0x2C) with a sync layer; anchor on dtor/ctor/CreateInstance

- status: works
- tags: resort,RP,SaveDataMgr,layout
- source: rp-savedatamgr worker 2026-11-09

symptom: 6/13 over a 0x304 split of a 0x2030 object
cause: Resort rewrote the class; ogws order/sizes do not apply
fix: recover fields from ctor offsets, write source in Resort's address order; IRPSysHostIOSocket dtor inline empty; NANDCreate perms 0x35; explicit parentheses for the cluster-count sum; if/else (not early return) for loadSync's error block; 0x802338B0 is resetSaveData (the fuzzy isSaveFileBroken was wrong)
