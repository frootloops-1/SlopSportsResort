# resort: PCH header edits renumber @N locals; matched units drop to 99.9% in objdiff

- status: works
- tags: resort,objdiff,symbols,pch,tools
- source: 2026-11-09

symptom: a Matching unit shows 99.9% after an unrelated header change, DOL still OK
cause: MWCC numbers anonymous locals per TU; any header in the SportsPack prefix shifts them, and objdiff pairs data by name
fix: after header changes run python3 tools/sync_local_names.py --apply (pairs @N by order per section inside each Matching unit's split)
