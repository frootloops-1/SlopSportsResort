# resort library: asm_diff.py does not rebuild

- status: works
- tags: resort,library,port

symptom: variant sweeps show no change
cause: stale object
fix: run verify.py (or ninja) before asm_diff
