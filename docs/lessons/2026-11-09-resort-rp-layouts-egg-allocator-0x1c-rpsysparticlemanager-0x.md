# resort: RP layouts EGG::Allocator 0x1C, RPSysParticleManager 0xC0, Unk_806B98E0 0x158, HomeMenuMgr flags 0x4C-0x51

- status: works
- tags: resort,rp,data

symptom: offset diffs in RPSysScene/EffectMgr
cause: Resort grew these classes
fix: Allocator mHeap 0x14 mAlign 0x18; ParticleManager mpParam 0xBC; HomeMenuMgr timer 0x8, f32[4][4] 0xC, state 0x54, rest +0x40
