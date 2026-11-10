# resort: Canoeing layout ctors stuck at ~96.5% on strncpy address scheduling

- status: fails
- tags: resort,layout,canoeing
- scope: resort
- source: can-fld

symptom: layout ctors differ only in strncpy src/dst address computation order
cause: unknown
fix: failed: nm local, static inline SetName helper, Wkb ctor form
