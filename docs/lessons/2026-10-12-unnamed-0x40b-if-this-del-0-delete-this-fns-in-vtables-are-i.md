# Unnamed 0x40B 'if(this&&del>0) delete this' fns in vtables are implicit inline subclass dtors; rename vtables/dtors in symbols.txt

- status: works
- tags: dtor,vtable,inline,symbols.txt,Construct,DrawPath
- scope: RPGrpDrawPathManager
- source: sonnet worker + coordinator 2026-10-12

symptom: fn_XXXX placeholders and lbl_ vtables score 0 though our weak dtors/vtables are identical
cause: objdiff pairs by name
fix: Map placeholder to class by which lbl_ vtable the Construct<T> loads; rename to __dt__/__vt__ (weak for subclasses; key-function class vtable global). Defining the key virtual (scnProcDraw) in the cpp makes CW emit vtable + inline dtor. Class sizes: li r3,N before __nw gives real size (Bloom 0x34)
