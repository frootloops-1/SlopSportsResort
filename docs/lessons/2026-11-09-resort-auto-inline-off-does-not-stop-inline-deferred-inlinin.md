# resort: auto_inline off does not stop -inline deferred inlining a member; push/dont_inline on/pop does

- status: works
- tags: resort,inline,pragma
- scope: resort
- source: rp9-renderer

symptom: BecomeCurrent inlined into Construct and Rendering (Construct 82.8%)
cause: -inline deferred auto-inlines small members regardless of #pragma auto_inline off
fix: #pragma push / #pragma dont_inline on / #pragma pop around the callee definition (Construct -> 100)
