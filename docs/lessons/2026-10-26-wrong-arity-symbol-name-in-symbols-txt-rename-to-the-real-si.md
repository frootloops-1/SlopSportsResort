# Wrong-arity symbol name in symbols.txt: rename to the real signature, delete the extern C alias

- status: works
- tags: symbols,rename,extern-c,CopyFromG3D,eggLightManager
- scope: egg/gfxe

symptom: extern C alias needed for a callee whose symbols.txt name has extra unused params; LoadScnLightInner extra li r5/r6
cause: CopyFromG3D mangled name carried (LightObject*, bool) that the body never uses and callers never pass
fix: rename symbol to ...ResAnmLightf, drop the 2 params in header+definition, call pObj->CopyFromG3D(light, frame); eggLightObject 15/15, LoadScnLightInner stays 99.57, DOL 0 diff
