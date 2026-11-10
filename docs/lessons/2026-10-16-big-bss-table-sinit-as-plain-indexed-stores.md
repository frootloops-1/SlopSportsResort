# big bss table sinit as plain indexed stores

- status: works
- tags: sinit,bss,ctors,rpbsb
- source: RPBsb_80273950 2026-10-16

symptom: 784B sinit filling a 0x1C-stride table
cause: -
fix: t[e].field = const in field order; .ctors via __declspec(section ".ctors") static ptr + force_active on (100% first try)
