# Inline helpers emitted as bl: TU-wide #pragma dont_inline

- status: works
- tags: inline,pragma
- scope: RPGol_802ae9ec
- source: fn_802AEAA0

symptom: bl restart__6GolAnmFv instead of inlined body
cause: dont_inline on covering whole TU
fix: restrict dont_inline to thunks+dtor; keep this-adjust thunk inside or its callee inlines into it
