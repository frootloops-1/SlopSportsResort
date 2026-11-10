# Correction: 'extra weak vtable/dtor/policyTable in our .o' is NOT a reason a flip fails

- status: works
- tags: correction,weak,dedupe,layout
- scope: RPGraphics
- source: coordinator 2026-10-12

symptom: Earlier notes blamed weak extras (RPGrpScreen vtable, base dtor, policyTable) for DOL diffs
cause: Linker dedupes weak data; only section sizes / gap symbols / strong symbol placement matter
fix: Diagnose DOL diffs by section size words and offset deltas before chasing weak emission order
