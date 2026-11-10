# Descriptor::set(const PaneView*) + non-const Cursor getters closes the inlined set(pane) load-scheduling/CSE wall (fn_801C8A08 90.4 -> 100)

- status: works
- tags: scheduler,cse,const,RPUtlLytFrameCursor,RPUtl_801C9E7C,set-pane
- scope: Pack/RPUtility
- source: claude 2026-11-02

symptom: 8 inlined Descriptor::set(PaneView*) copies: size lfs scheduled after cold MTX lwz; retail CSEs pane loads (matrix word, previous.valid) across strcpy; 2 insns longer
cause: pane pointer was non-const so every call kills loads; const pointee lets MWCC CSE/schedule as retail. Remaining residue was origin colouring and store order, then const-ness of Cursor helpers
fix: set(const PaneView*), isCurrentPane(const PaneView*), fn param const PaneView*; use pane->origin directly (originX = pane->origin % 3; originY = pane->origin / 3, no local); write scale.x/scale.y stores (from sx/sy locals) BEFORE the mtx copy; make Cursor::getPrevious()/previousValid() NON-const (const made a reload of previous.valid). Also .ctors entry needs #pragma force_active on + const initializer or the linker drops it (DOL -4 bytes). Port to RPUtl_801C9E7C fn_801CA3DC (same wall).
