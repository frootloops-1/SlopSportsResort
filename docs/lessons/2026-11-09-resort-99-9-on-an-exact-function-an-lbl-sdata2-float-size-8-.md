# resort: 99.9% on an exact function = an lbl_ sdata2 float (size 8) not pairing with the compiler's @N

- status: works
- tags: resort,objdiff,sdata2,symbols
- source: rp-egg-layouts worker 2026-11-09

symptom: function code identical but objdiff 99.9%
cause: dtk label lbl_X sized 8 (with padding) vs object local @N size 4
fix: rename the lbl_ to the object's @N, size 0x4, scope:local (objdump -t on the built .o); name vtable lbl_ labels after the class
