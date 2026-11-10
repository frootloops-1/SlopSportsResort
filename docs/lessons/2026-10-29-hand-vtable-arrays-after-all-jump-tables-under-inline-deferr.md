# Hand vtable arrays after all jump tables under -inline deferred: #pragma defer_codegen off before them flushes deferred codegen

- status: works
- tags: vtable,data-order,defer_codegen,jumptable,anchor,rpbox,802cf93c
- scope: mwcc
- source: claude/box802cf-data-1029

symptom: RPBox_802cf93c: explicit void* vtable arrays defined at END of a descending-order -inline deferred file still landed at .data start (before every @N/jump table) and 6+ exact functions switched to ...data.0 anchor addressing (fn_802D4E64 100 -> 71.6)
cause: with deferred codegen, file-scope data is emitted at parse time while functions (and their jump tables) are codegen'd at TU end, after seeing the definitions (so same-TU .data objects get anchored). __declspec(weak) stops the anchoring but not the order
fix: put '#pragma defer_codegen off' right before the arrays: it flushes all pending deferred functions first, so jump tables precede the arrays and the functions still treat them as extern (no anchor). .data 28.49 -> 100, 0 code regressions
