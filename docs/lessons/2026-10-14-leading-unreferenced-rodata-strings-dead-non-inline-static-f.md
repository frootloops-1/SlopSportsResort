# Leading unreferenced .rodata strings: dead non-inline static fn defined LAST pools them first

- status: works
- tags: rodata,strings,pool-order
- source: RPBsb_8027b2d4

symptom: 95.9%: string offsets 0x0C.. instead of after 0x58 bytes of unreferenced T_ names
cause: orig .rodata has strings with no referrer in this TU; pool must start with them
fix: dead static void f(){ g("T_..")x8 } as the LAST definition (reverse generation order); linker strips it, main.dol OK
