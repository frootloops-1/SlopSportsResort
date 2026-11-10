# Static-object sinit: separate file-scope statics share one base reg

- status: works
- tags: sinit,bss
- scope: RPGol_802b1a0c
- source: fn_802B4E60

symptom: base reg sharing differs
cause: struct/extern globals don't share base
fix: separate statics in address order: u8 node[0x10]; array; node; obj...; hand-written sinit with __construct_array/__register_global_object in .ctors
