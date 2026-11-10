# g3d res chain temps: declare ResMdl mdl; ResTev tev; ResMat mat; as locals in that order then assign (stack slots)

- status: works
- tags: rpgolmapobjtree,g3d,stack-slot
- scope: RPGolMapObjTree
- source: sonnet

symptom: chained inline temps swap mat/tev slots
cause: temp allocation
fix: locals declared mdl,tev,mat then assigned
