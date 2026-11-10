# Loop over linked list in renderer: wrap in static inline helper; x/2.0f vs x*0.5f; EGG asserts via inline helpers

- status: works
- tags: loop,helper,regalloc,fmuls,const,assert,StateGX,SetBinaryExtension,RPGrpRenderer
- scope: RPGrpRenderer
- source: sonnet worker 2026-10-12

symptom: iterator shares register with renderer ptr; fmuls operand order; extra assert strings in .data
cause: inline loop allocation; x*0.5f emits const-first fmuls; EGG::Frustum::SetProjectionType emits two asserts
fix: static inline void DrawAll(RPGrpRenderer*) helper; use x / 2.0f for fmuls f0,f0,f1; direct field-store inline helper (RPGrpScreen::SetProjectionOrtho); SetBinaryExtension needs EGG_ASSERT(pName != NULL) at #line 46 (5 inlined calls give 5 string pairs); vptr at last-declared virtual dtor
