# resort: RPSysEffectCreator is 0x78 with 8 effect/texture project slots (ctor 0x8023F748)

- status: open
- tags: resort,rpsyseffectcreator,layout,rpsyssystem

symptom: RPSysSystem::createEffectWork 99.9: new RPSysEffectCreator size and ctor differ
cause: Resort rewrote the class: projects are arrays [8] at 0x14/0x34, backSave 0x54 (=1), isSlow 0x58, frame 0x5C, frameRate 0x60, slowSystem 0x64, arrays[2] at 0x68/0x70
fix: Rewrite RPSysEffectCreator.cpp against this layout (do not pad the ogws header); a temporary pad + rename of fn_8023F748 gives createEffectWork 100
