# Golf layout-wrapper family matches with sibling-TU local-struct style

- status: works
- tags: golf,layout,vtable,RPSysLayout
- scope: RPGol_802bf4f8
- source: sonnet-worker

symptom: isDone/draw/reset/init/calc wrappers around RPSysLayout at 0xC
cause: same shape as RPGol_802c0c38
fix: copy RPGol_802c0c38 conventions: local structs, extern C void* lbl[12] vtables, no shared headers
