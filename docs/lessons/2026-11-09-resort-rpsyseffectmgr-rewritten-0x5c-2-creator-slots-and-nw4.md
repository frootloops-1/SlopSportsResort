# resort: RPSysEffectMgr rewritten (0x5C, 2 creator slots) and nw4r ef headers on the Resort layout

- status: works
- tags: resort,rpsyseffectmgr,nw4r,ef,layout

symptom: RPSysEffectMgr 4/64 on the ogws source
cause: Resort ef: EffectSystem 0xC06C, CreationQueue entries 0x30, DrawInfo 0xA0 (assign colour b,g,r,a), TextureData keeps lod_bias, memory manager 0x3C; Mgr has TBitFlag<u32>[16] at 0x1C and a heapless CreateInstance
fix: Mgr 55/64, Creator 17/18. Left: Unk_806B98E0 (0x158) as TEffect, RPSysParticleManager 0xC0 (header says 0xD8)
