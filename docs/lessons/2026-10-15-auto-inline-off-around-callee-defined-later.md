# auto_inline off around callee defined later

- status: works
- tags: inline
- scope: RPTnsScene
- source: claude/rptns-3

symptom: fn_8024CE14 inlined into fn_8024D358
cause: -inline deferred inlines later-defined callee
fix: #pragma auto_inline off / reset around callee
