# resort: double store of a member = inline reset() shared by ctor and Initialize

- status: works
- tags: resort,rp

symptom: member = NULL then reassigned
cause: inline helper
fix: add reset() and call it in both; cleared ledger #29
