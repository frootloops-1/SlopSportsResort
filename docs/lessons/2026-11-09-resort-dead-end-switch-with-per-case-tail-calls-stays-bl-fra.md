# resort: dead end - switch with per-case tail calls stays bl + frame

- status: fails
- tags: resort,swf,switch
- scope: resort
- source: swf-template-batch-2026-11-09

symptom: fn_8062B3BC 25%: retail tail-calls per case
cause: unknown; return f(...) per case still emits bl with a frame
fix: parked
