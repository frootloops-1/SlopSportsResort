# Same-TU empty/small extern C callees get inlined

- status: works
- tags: mwcc,inline,dont_inline

symptom: bl to a small fn_ in same TU disappears
cause: CW inlines stubs and small callees into callers
fix: wrap callee in #pragma dont_inline on/reset (keep narrow)
