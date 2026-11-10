# -inline deferred auto-inlines a same-TU callee into later-emitted caller

- status: works
- tags: inline,deferred,pragma,auto_inline
- scope: RPGol_802c58d4
- source: claude/rpgolscene-unsplit

symptom: callee body appears inside the caller; callee still emitted
cause: -inline deferred sees whole TU
fix: wrap the callee definition in #pragma push / #pragma auto_inline off / #pragma pop
