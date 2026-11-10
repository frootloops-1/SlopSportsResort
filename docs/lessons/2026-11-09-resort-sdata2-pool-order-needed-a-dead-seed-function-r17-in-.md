# resort: .sdata2 pool order needed a dead seed function (R17) in RPGrpCamera

- status: open
- tags: resort,sdata2,pool-order,R17
- source: rp-camera review 2026-11-09

symptom: 4 functions load constants from shifted slots; DOL 55 bytes off
cause: pool order follows emission order (-inline deferred: last definition first); the real early-emitted user of 1.0f/-1.0f/0.0f is unknown
fix: marked MATCH-PENDING (R17) PoolSeed at file end (marker-ledger #2); find the real last-defined function/inline using those literals to remove it
