# resort: IRPSysHostIOSocket has no virtual dtor (vtable {0,0,ListenPropertyEvent,GenMessage})

- status: works
- tags: resort,IRPSysHostIOSocket,vtable
- scope: resort
- source: RP batch 5 (2026-11-09)

symptom: derived vtables (RPSysSaveDataMgr) misordered; ogws IRPSysHostIOSocket.cpp fails with dtor redefined
cause: Resort dropped the base virtual dtor; derived classes add theirs after the base slots
fix: remove the dtor from the header; IRPSysHostIOSocket.cpp Matching from ogws source
