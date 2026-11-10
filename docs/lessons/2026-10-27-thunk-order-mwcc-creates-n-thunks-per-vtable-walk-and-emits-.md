# Thunk order: MWCC creates @N@ thunks per vtable walk and emits them in reverse; an earlier vtable reorders them

- status: works
- tags: thunk,vtable,multiple-inheritance,emission-order
- scope: egg/gfxe/eggDrawPathBase
- source: drawpathbase-1027

symptom: eggDrawPathBase: @112@scnProcDraw emitted before @112@__dt__ (retail: dt first), 9 DOL bytes; vtable itself correct
cause: thunks are created when a vtable is generated (walk in secondary-base slot order) and emitted in reverse creation order; a thunk that already exists is reused. Template bases are walked in reverse (forward emission).
fix: add an unreferenced derived class after the last definition with an out-of-line ctor (class X : public DrawPathBase { X(); }; X::X() {}); its vtable is generated first and creates the shared scnProcDraw thunk, so DrawPathBase's walk only adds dt, giving dt then scnProcDraw. The linker strips the class. MATCH-PENDING R17 + ledger row 23. DOL 0 bytes.
