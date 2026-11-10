# verify.py KeyError base_path for new unit

- status: works
- tags: tooling

symptom: KeyError base_path
cause: objdiff.json generated before source file existed
fix: run python3 configure.py (no edits) to regenerate
