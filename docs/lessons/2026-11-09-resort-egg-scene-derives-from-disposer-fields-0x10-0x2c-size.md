# resort: EGG::Scene derives from Disposer (fields 0x10-0x2C, size 0x30)

- status: works
- tags: resort,egg,scene,layout

symptom: RPSysScene stuck at 17/37 on scene field offsets
cause: Resort EGG::Scene ctor 0x801C82A4 calls the Disposer ctor; heaps 0x10-0x1C, parent 0x20, child 0x24, sceneID 0x28 (-1), mgr 0x2C
fix: Header changed; RPSysScene 17 -> 27. Watch for sources that only matched through the old offsets (RPSysSaveDataMgr::initBanner used getHeap_Debug for a 0x10 read: it is getHeap)
