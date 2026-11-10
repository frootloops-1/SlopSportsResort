# RPUtl_801C9E7C fn_801CA3DC closed with the RPUtlLytFrameCursor recipe (90.3 -> 100)

- status: works
- tags: scheduler,cse,const,RPUtl_801C9E7C,set-pane
- scope: Pack/RPUtility
- source: claude 2026-11-02

symptom: fn_801CA3DC 90.3: 8 inlined Descriptor::set(PaneView*) schedule/CSE wall
cause: non-const pane pointer; local horizontal/vertical origin; scale stores after mtx copy; const Cursor getters
fix: set/isSamePane/fn take const PaneView*; scale.x/scale.y stores right after the w/h reads (before mtx copy); originX = pane->origin % 3 and originY = pane->origin / 3 with no locals; getPrevious()/hasPrevious() non-const (getCurrent stays const). Then .sdata2 lbl_804C1C5C..68 -> @9006-@9009 size 4 scope:local and .ctors force_active const initializer: unit 10/10, all sections 100%, DOL 0. Markers (d1,d2; isSamePane target; dead 1.0f) still each needed (rechecked).
