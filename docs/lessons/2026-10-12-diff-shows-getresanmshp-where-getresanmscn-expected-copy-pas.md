# Diff shows GetResAnmShp where GetResAnmScn expected: copy-paste case

- status: works
- tags: copy-paste,GetResAnmScn,switch,case
- scope: RPGrpModelResManager
- source: sonnet worker 2026-10-12

symptom: 99.96-99.97% near-miss with a differing call symbol in the ResAnmScn case
cause: Source calls the wrong getter in a copy-pasted switch case
fix: Check every Type_ResAnmScn case (GetPtr x2, HasFile)
