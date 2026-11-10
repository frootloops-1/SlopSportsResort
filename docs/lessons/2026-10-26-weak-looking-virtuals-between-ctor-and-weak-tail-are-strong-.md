# Weak-looking virtuals between ctor and weak tail are strong out-of-line defs in this TU

- status: works
- tags: order,weak,virtual,key-function,symbols
- scope: Pack/RPGraphics/RPGrpModelManager
- source: claude/data-grp-1026

symptom: text order ct,GetVersion,dt,SetBinaryInner,GetBinaryInner then weak GetBinarySize,dt; extern C __dt__14RPGrpModelMisc stand-in matched a misnamed symbol
cause: the class virtuals were declared in the header and defined out of line in this .cpp (the key function keeps the vtable here); symbols.txt had dtor named without Fv
fix: rename symbol to __dt__14RPGrpModelMiscFv; define the virtuals out of line before the ctor in reverse address order; making GetBinaryInner inline moves the vtable to the GetBinaryType TU (dead end)
