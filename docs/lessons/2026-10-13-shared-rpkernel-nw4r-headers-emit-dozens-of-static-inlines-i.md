# Shared RPKernel/nw4r headers emit dozens of static inlines into a split TU

- status: works
- tags: include,static-inline,text-size,local-view
- scope: RPGol_802c68a4
- source: claude/rpgolscene-unsplit

symptom: objdiff fn scores fine but our .text 2008B vs 1412B; dtk elf disasm lists MEMGetHeapEndAddress, GXSetViewportv, OSf32tos16 ... as local fns
cause: Pack/RPKernel/RPSysLytAnmObj.h pulls revolution/nw4r headers whose static inline fns are emitted in this compiler config
fix: use minimal local class views (Pane with mFlag at 0xB7 + SetVisible, frame ctrl copy, RPSysLytAnmObj with inline restart/isFinished); check emitted fns with dtk elf disasm <o> | grep ^.fn
