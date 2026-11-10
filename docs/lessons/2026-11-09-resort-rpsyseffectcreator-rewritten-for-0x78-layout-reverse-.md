# resort: RPSysEffectCreator rewritten for 0x78 layout, reverse source order: 10/16

- status: works
- tags: resort,rpsyseffectcreator,layout,order

symptom: ogws source scored 0/16
cause: Resort has 8 effect/texture project slots, no mpMemoryManager (update reads mpSlowSystem->GetMemoryManager()), main-system Calc moved to its own function; the TU emits .text in reverse source order and also emits weak EmitterParameter/ParticleParameter ctors at 0x8023FE3C/40
fix: Header + source rewritten; 10/16 exact. Remaining 6 need Resort nw4r ef EffectSystem (0xC06C, SortEffect, SetProcessCamera, CreateEffect(EmitterResource*)), RPSysEffectMgr methods 0x8023D5C4/5DC/604 and the Resort RPSysEffectMemoryManager (0x3C). Keep the ogws alloc form in createSlowSystem until that header is fixed
