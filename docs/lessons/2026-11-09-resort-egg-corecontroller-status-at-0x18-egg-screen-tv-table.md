# resort: EGG CoreController status at 0x18; EGG::Screen TV table one 0xC struct array

- status: works
- tags: resort,rp

symptom: offset diffs
cause: Resort EGG revision
fix: mUnk14 added (getCoreStatus 0x801C4380, stride 0xF0); sTVModeInfo at 0x806B4AD8
