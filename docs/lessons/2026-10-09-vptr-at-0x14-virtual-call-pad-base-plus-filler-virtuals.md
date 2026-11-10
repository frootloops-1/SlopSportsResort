# Vptr-at-0x14 virtual call: pad base plus filler virtuals

- status: works
- tags: RPGolFieldManager,vtable

symptom: manual fn-ptr cast loads vptr into wrong reg
cause: CW
fix: plain 0x14-byte base + filler virtuals + real virtual; slot offset 8+4*idx
