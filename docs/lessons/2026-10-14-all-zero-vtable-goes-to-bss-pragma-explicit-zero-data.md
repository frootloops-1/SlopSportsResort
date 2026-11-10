# All-zero vtable goes to .bss: #pragma explicit_zero_data

- status: works
- tags: data,bss
- scope: RPGol_802a7a40
- source: fn_802A7B80

symptom: zero array in .bss not .data
cause: zero-init data placed in bss
fix: #pragma explicit_zero_data on / reset around the definition
