# -inline deferred unit emits functions in reverse

- status: works
- tags: RPBox,R17
- scope: Pack/RPSports/RPBsbScene/RPBsb_8025a3e8

symptom: -inline deferred unit emits functions in reverse
cause: -inline deferred unit emits functions in reverse
fix: #pragma defer_codegen off + reorder; local static dtor helper right after owner
