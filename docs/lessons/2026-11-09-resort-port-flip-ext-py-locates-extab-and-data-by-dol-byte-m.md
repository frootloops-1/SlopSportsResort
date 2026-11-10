# resort: port_flip_ext.py locates extab and data by DOL byte match

- status: works
- tags: resort,library,port,flip

symptom: port_flip skips units with extab or unlocated small data
cause: port_flip has no extabindex lookup
fix: tools/port_flip_ext.py (same usage); its fallback can pick wrong sizes, so always run port_sizecheck.py
