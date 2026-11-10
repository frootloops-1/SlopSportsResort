# vptr placed at first virtual's position

- status: works
- tags: vptr,struct,rpbsb
- source: RPBsb_80283fe0 2026-10-16

symptom: need vptr at nonzero offset
cause: MWCC puts vptr where the first virtual is declared
fix: struct V{u8 pad[8]; virtual vf08(); ...} gives vptr at 8; no base pad trick needed
