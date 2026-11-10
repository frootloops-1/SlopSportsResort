# resort: RPSysSystem keeps NAND/DVD/WC24 thread info behind a pointer at 0x4C

- status: works
- tags: resort,RP,RPSysSystem,layout
- source: rp-savedatamgr worker 2026-11-09

symptom: requestNandFunc / isSceneChangeEnable read 0x4C then +0..+0xC
cause: Resort moved the thread members into a separate struct
fix: NandTaskInfo {nand, dvd, wc24, endMessage} behind mpNandInfo with inline accessors (still a union with the Wii mFrameRate until RPSysSystem.cpp is matched); run report_cmp after shared-header edits: sibling units confirm or refute the layout
