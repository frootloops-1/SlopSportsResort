# LoadScnLightInner extra li r5/r6 at CopyFromG3D: symbol-named callee has 2 extra params the original does not pass

- status: works
- tags: egg,eggLightManager,arity,symbols
- scope: egg/gfxe/eggLightManager

symptom: ours emits li r5,0; li r6,0 before bl CopyFromG3D (98.3)
cause: symbols.txt name CopyFromG3D...fPQ23EGG11LightObjectb has trailing (LightObject*, bool) unused by callee; original call passes only (obj, anm, frame)
fix: extern C alias with raw symbol name and 3-arg shape in eggLightManager.cpp -> 99.6 (same pattern as LightTextureManager)
