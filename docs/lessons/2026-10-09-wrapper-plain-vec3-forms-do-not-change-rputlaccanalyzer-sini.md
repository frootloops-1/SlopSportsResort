# Wrapper/plain VEC3 forms do not change RPUtlAccAnalyzer sinit

- status: fails
- tags: sinit,scheduling
- scope: RPUtlAccAnalyzer
- source: claude-opus

symptom: sinit 94.9%
cause: vector init canonicalized; difference was on the color side
fix: failed: wrapper ctor with args, raw float members, plain VEC3+separate u32 (bss 75%), extern-predeclared swapped definition order (layout follows definition, 74.9%), per-field ColorEntry ctor (55.9%), single combined struct (65.6%)
