# Inline overloads fail inside extern C

- status: fails
- tags: mwcc,extern-c
- source: RPGol_802b90b4

symptom: error 10197
cause: C linkage forbids overloads
fix: give inline helpers distinct names
