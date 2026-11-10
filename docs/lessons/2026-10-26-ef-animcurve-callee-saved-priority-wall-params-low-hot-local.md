# ef_animcurve callee-saved priority wall (params low, hot locals high)

- status: open
- tags: ef_animcurve,regalloc,callee-saved
- scope: src/nw4r/ef/ef_animcurve.cpp

symptom: Child/U8/F32/Texture differ only in saved-reg order: orig params lowest, pHeader/tables/loop locals highest
cause: unknown; not compiler version (GC/3.0a5, 3.0a3.4 identical, Wii/* worse), not decl order (~250 builds)
fix: open; try call-site/use-count shape of createChild loops, pHeader==pCmdList coalescing
