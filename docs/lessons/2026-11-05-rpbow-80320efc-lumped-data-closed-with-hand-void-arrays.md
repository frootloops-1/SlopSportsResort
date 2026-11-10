# RPBow_80320EFC lumped .data closed with hand void* arrays

- status: works
- tags: rpbow,data,vtable

symptom: .data 0% for 0x803CA430-0x803CA5F0 whose slot fns live in other units
cause: no definitions in the unit
fix: hand void* arrays at file end, vtable externs changed to void*[] with (u8*) casts at +offset uses: .data 100
