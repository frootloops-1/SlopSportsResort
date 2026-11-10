# resort: 99.x functions with identical asm_diff are .sdata2/.rodata pool or reloc naming, not code

- status: works
- tags: resort,bowling,sdata2,triage
- scope: resort
- source: bowling-lanes

symptom: dozens of Bowling functions at 98.8-99.9 with identical instructions
cause: float/string pools still owned by other units or still ogws-named; objdiff scores reloc names
fix: do a data-assignment pass (unit .sdata2/.rodata ranges, Resort pool names) instead of touching code. Also: objdiff can show 100.0 with a differing immediate; trust verify fns-exact and asm_diff
