# resort: RPSysEffect rewritten: dtor-only vtable, 0x98-byte parameter object at 0x80, file 0x8023E1D4-0x8023EB18

- status: works
- tags: resort,RPSysEffectBase,layout,split
- scope: resort
- source: RP batch 4 (2026-11-09)

symptom: RPSysEffectBase 6/31 with many unnamed 8-byte forwarders and setters; ctor/dtor/sinit in an unk sinit unit
cause: Resort moved parameter setters to a member object (extra u32 mode arg), two ctors with strncpy(32); unit includes only RPSysEffectBase.h+RPSysEffectMgr.h (RPKernel.h pulls a g3d cm2hw sdata2 const)
fix: Resort layout in RPSysEffectBase.h, placeholder classes Unk_806B9908/Unk_806B98E0, merged split; 35/35 Matching
