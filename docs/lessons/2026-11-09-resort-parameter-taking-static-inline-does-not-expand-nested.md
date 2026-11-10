# resort: parameter-taking static inline does not expand nested inline getters

- status: works
- tags: resort,inline,RPGrpRenderer
- scope: resort
- source: rp9-renderer

symptom: original calls GetNext/GetCurrentView/GetCurrentScreen out of line (weak copies) inside a helper
cause: MWCC does not expand inlines nested in a parameter-taking static inline; parameter-less inlines do expand
fix: put the getter call inside a parameter-taking inline helper (DrawAll-style); closed fn_80254AE8's GetCurrentScreen call
