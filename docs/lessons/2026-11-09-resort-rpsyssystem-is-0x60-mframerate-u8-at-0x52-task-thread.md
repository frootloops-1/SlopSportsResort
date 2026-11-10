# resort: RPSysSystem is 0x60 (mFrameRate u8 at 0x52, task-thread object* at 0x4C); file 0x8022D328-0x8022E3A8, main separate

- status: works
- tags: resort,RPSysSystem,layout,split
- scope: resort
- source: RP batch 5 (2026-11-09)

symptom: RPSysSystem 0/27, union at 0x4C, file ends unclear
cause: Resort added heaps, a mutex and a nand/dvd/wc24 task-thread object; mainLoop/loadFrameWork moved to another unit near 0x80237xxx; weak ConfigData getters + sinit close the file
fix: real layout in RPSysSystem.h, union removed; 37/39 (initialize 98.7 and createEffectWork 99.7 wait on Resort EGG Video/Xfb/AsyncDisplay/ProcessMeter and audio-arg types)
