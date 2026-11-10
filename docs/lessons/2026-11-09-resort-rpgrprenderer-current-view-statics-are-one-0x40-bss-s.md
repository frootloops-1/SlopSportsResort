# resort: RPGrpRenderer current-view statics are one 0x40 bss struct sCurrent at 0x807CEEF0

- status: works
- tags: resort,RPSysTextWriter,RPGrpRenderer,layout
- scope: resort
- source: RP batch 4 (2026-11-09)

symptom: RPSysTextWriter Begin/cursor helpers load the screen pointer via lis/addi + lwz 0x3C instead of an sda static
cause: Resort groups viewNo(+0), view(+4), view MTX(+8), camera(+0x38), screen(+0x3C) into one struct
fix: static struct member RPGrpRenderer::sCurrent; RPSysTextWriter went 2/11 -> 15/15 (real file end includes ctor + CreateInstance, no DestroyInstance)
