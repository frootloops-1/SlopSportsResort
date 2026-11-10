# DrawPathBase @112@ thunk order: more dead ends; order = descending IScnProc slot, unaffected by source order

- status: fails
- tags: thunk,vtable,multiple-inheritance,egg
- scope: egg/gfxe/eggDrawPathBase
- source: drawpathbase-1027

symptom: eggDrawPathBase Matching-link: 9 DOL bytes, @112@scnProcDraw thunk before @112@__dt (target: dt first); .text/.data 100% in objdiff
cause: secondary vtable relocs/thunks are generated in descending slot order (swapping IScnProc virtual decl order flips the thunks but also the vtable). Not affected by: explicit inline dtor first/last in DrawPathBase, scnProcDraw declared first, definition order of ct/scnProcDraw, FORCEDTOR helper before ct or after scnProcDraw, removing helpers, -inline auto,deferred/deferred/noauto
fix: unsolved; unit left NonMatching. Untried: unknown source construct that creates the dt thunk before the vtable is generated
