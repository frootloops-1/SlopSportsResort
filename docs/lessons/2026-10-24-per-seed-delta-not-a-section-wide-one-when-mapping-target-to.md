# Per-seed delta, not a section-wide one, when mapping target to our data section positions

- status: works
- tags: tooling,symbols,data-ref
- scope: project
- source: claude

symptom: section-wide offset between target and ours was inconsistent whenever our object had extra/missing symbols
cause: ours and target partitions differ, so a single translation does not hold
fix: derive the offset from each mismatching relocation row ((T.value+ta)-(O.value+oa)), group seeds by offset, verify with a byte compare; gate with ninja+DOL+near-miss and bisect on failure (tools/data_fix.py plan --verify)
