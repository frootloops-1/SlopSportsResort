# Called fn_ vanishes when callee is trivial stub

- status: works
- tags: inline

symptom: call missing, 76.9%
cause: stub body inlined
fix: write the real callee body
