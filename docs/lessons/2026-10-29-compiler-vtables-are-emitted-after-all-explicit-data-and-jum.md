# Compiler vtables are emitted after all explicit .data and jump tables (MWCC)

- status: fails
- tags: vtable,data-order,polymorphic,ctor,rpbox,802c8360
- scope: mwcc
- source: claude/q-boxrename-1029

symptom: replacing explicit vtable arrays with a real polymorphic class (BoxStat : BoxStatBase) fixed the ctor code but moved the two vtables from mid-.data to the end, after lbl_803C89C8 and the @1268 jump table
cause: MWCC writes explicit data definitions and normal-codegen jump tables first (in source/codegen order, defer_codegen on/off irrelevant), then all compiler vtables at end of TU, then late weak functions referenced only from vtables (their jump tables follow the vtables). Strong vtables (key function defined in TU) also go at the end
fix: a compiler vtable can only precede data that is itself emitted late (other compiler vtables, jump tables of weak vtable-only functions); in a TU that emulates some vtables as explicit arrays, keep the emulation (or model all of them as real classes). An out-of-line non-inline base dtor defined before the ctor emits at the right .text slot and is still auto-inlined into the derived dtor; an inline base dtor emits after the first user
