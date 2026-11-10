# Nested call args evaluate right-to-left in MWCC

- status: works
- tags: evaluation-order

symptom: callee order swapped for f(a(), b())
cause: MWCC evaluates args right to left
fix: use locals to force a() first
