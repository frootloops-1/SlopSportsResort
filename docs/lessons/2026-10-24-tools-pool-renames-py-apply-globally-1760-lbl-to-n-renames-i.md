# tools/pool_renames.py --apply globally: 1760 lbl_ to @N renames in one go

- status: works
- tags: pool,symbols,f1,data-ref
- scope: project
- source: claude

symptom: functions with identical code score <100 because target relocs name lbl_XXXX while ours name @N
cause: symbols.txt still had dtk lbl_ names for pooled constants
fix: python3 tools/pool_renames.py --apply (verified bytes+addends); rebuild, dol_diff 0 bytes, sym_addr_check unchanged (2026-10-24: 1760 renames, near-miss items 689->663). Re-run after every new first-source unit
