# Same-TU callee defined later gets inlined (inline deferred)

- status: works
- tags: inline,pragma
- scope: RPGol_802a7a40
- source: fn_802A9854

symptom: callee body inlined into caller
cause: deferred inlining
fix: #pragma dont_inline on / reset around that one definition
