# auto_inline off keeps a callee out-of-line without blocking its inlines

- status: works
- tags: inline,pragma
- scope: Pack/RPSports/RPBoxScene/RPBox_802cb9cc
- source: claude-rpbox-802cb9cc-1022

symptom: small extern C function got auto-inlined into a later caller; dont_inline on broke inlines inside it
cause: -inline deferred auto-inlines small functions; dont_inline also stops inlining inside the function
fix: #pragma auto_inline off / reset around the callee definition
