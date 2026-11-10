# resort: placement new adds a null check; for ctor-shaped free functions

- status: fails
- tags: resort,bowling

symptom: extra null test / operator new clash in extern C
cause: placement new semantics
fix: no clean fix yet; hand-calling __ct__ is MATCH-PENDING (ledger #30), model the class instead
