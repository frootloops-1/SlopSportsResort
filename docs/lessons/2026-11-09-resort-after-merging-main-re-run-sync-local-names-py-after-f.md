# resort: after merging main, re-run sync_local_names.py AFTER flipping (it skips NonMatching units)

- status: works
- tags: resort,tools,merge,pch,objdiff
- source: 2026-11-09

symptom: a just-matched unit shows 10/14 after merging main though the flip gate passes
cause: header changes on main renumber the unit's @N; the sync tool only touches Matching units
fix: flip_gate --keep, then sync_local_names.py --apply, then verify
