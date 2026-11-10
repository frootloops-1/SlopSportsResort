# Small extern C fn auto-inlined into later callers

- status: works
- tags: rpbox,auto_inline
- source: RPBox_802cf93c

symptom: callee body inlined, 60.9%
cause: auto_inline
fix: #pragma auto_inline off/reset around the definition (->96.6)
