# resort bowling: stale ogws_fn_* stubs with no Resort counterpart leave lbl_803CAxxx undefined

- status: works
- tags: resort,bowling

symptom: undefined Wii Sports label at link
cause: stub ported from ogws has no Resort function
fix: delete the stub instead of relabelling (RPBow_80329658 lbl_803CA650)
