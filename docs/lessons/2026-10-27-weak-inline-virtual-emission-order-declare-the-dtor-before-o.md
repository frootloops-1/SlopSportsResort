# Weak inline-virtual emission order: declare the dtor before other in-class virtuals

- status: works
- tags: emission-order,weak,dtor,vtable,egg
- scope: egg/gfxe/eggLightManager
- source: claude/lm-1027 5b664007c

symptom: Flipped eggLightManager linked GetBinarySize,GetVersion,__dt__ but orig has __dt__ first; objdiff 100% on all three
cause: MWCC emits vtable-referenced in-class inline virtuals in class declaration order, not vtable-slot order
fix: Move 'virtual ~LightManager() {}' to right after the ctor in the class; a new virtual dtor keeps slot 0x1C, so vtable is unchanged
