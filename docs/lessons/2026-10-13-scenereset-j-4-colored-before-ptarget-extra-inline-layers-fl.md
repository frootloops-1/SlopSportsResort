# sceneReset: j*4 colored before pTarget; extra inline layers flip j and j*4

- status: fails
- tags: regalloc,coloring,sceneReset,loop
- scope: Pack/RPKernel/RPSysControllerMgr

symptom: sceneReset 98.2% j*4 r28 vs r23
cause: coloring order; locals declared earlier colored first (higher reg)
fix: 15 hypothesis families failed (inner getter inline, inner loop inline, init forms, decl positions); closest 97.9. Park or permuter on GetCtrl variant
