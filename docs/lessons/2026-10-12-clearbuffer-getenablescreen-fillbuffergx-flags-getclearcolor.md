# ClearBuffer: GetEnableScreen()->FillBufferGX(flags, GetClearColor()) colour-first order unresolved

- status: open
- tags: struct,by-value,arg-order,temp,RPGrpView,ClearBuffer
- scope: RPGrpView::ClearBuffer
- source: sonnet worker 2026-10-12

symptom: orig copies colour bytes first into one temp at 0xc(r1) then inlined GetEnableScreen
cause: unknown
fix: Named local GXColor copy gives 89.2% but adds a 2nd struct copy; const ref, pScreen local, moving def: no change (83.8)
