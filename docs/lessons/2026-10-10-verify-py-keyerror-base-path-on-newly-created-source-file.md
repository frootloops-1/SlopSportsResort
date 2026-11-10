# verify.py KeyError base_path on newly created source file

- status: works
- tags: verify,objdiff,worktree
- scope: tooling
- source: haiku

symptom: KeyError base_path after adding first .cpp for a NonMatching split
cause: objdiff.json generated before source existed
fix: run python3 configure.py in the worktree, then rerun verify
