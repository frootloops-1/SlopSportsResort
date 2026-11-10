# resort: EGG core layouts (Thread 0x4C, TaskThread 0x5C, Xfb 0x14, XfbManager 0x10, Display 0x2C, AsyncDisplay 0xC0, ProcessMeter 0x158)

- status: works
- tags: resort,egg,layout,rpsyssystem

symptom: RPSysSystem::initialize stuck at 98.7 on sizes and this-adjusts
cause: Resort EGG is newer than ogws: extra words in Thread (0x3C/0x40, link 0x44), Xfb (0x8), Display tick at 0x20; ProcessMeter PerformanceView base at 0x4C; Video::initialize/configure/getStandardRenderModeObj take a 10-entry render-mode table pointer
fix: Headers updated with evidence addresses; initialize 100. Xfb ctor 0x801C795C, XfbManager::attach 0x801C79F8, ProcessMeter ctor 0x801C84D0 named
