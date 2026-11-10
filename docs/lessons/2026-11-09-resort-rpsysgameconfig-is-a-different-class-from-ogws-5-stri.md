# resort: RPSysGameConfig is a different class from ogws (5 string + 11 int parms, no DestroyInstance)

- status: works
- tags: resort,RP,layout,singleton
- source: rp-gameconfig worker 2026-11-09

symptom: ctor 65%, object larger than split
cause: Resort rewrote the config: tag names in the unit's rodata, no DestroyInstance
fix: tag names from rodata strings, types from ctor calls (StringTagParm vs TagParm+vtable store), mirror set() store order; hand-write spInstance+CreateInstance instead of RP_SINGLETON_IMPL_EX; the dtor (vtable slot) was the file's first function, before the name-matched split
