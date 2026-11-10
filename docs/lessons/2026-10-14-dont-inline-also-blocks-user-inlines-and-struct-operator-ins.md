# dont_inline also blocks user inlines and struct operator= inside marked functions

- status: works
- tags: dont_inline,inline,pragma
- scope: RPTns_8023bd9c
- source: sonnet worker 2026-10-14

symptom: helpers stop inlining after adding #pragma dont_inline on
cause: pragma applies to calls made inside the marked functions too
fix: use macros, fieldwise copies, function-body asm blocks inside dont_inline regions (RPTns_8023bd9c)
