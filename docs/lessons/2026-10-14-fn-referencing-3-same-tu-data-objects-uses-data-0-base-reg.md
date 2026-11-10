# Fn referencing >=3 same-TU .data objects uses ...data.0 base reg

- status: works
- tags: data,addressing
- scope: RPGol_802a7a40
- source: fn_802AA044

symptom: base-register addressing, 94%
cause: MWCC data base pooling
fix: mark the manual vtable array __declspec(weak)
