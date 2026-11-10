# Unrolled poll loop reloads not CSE'd in target: source variants failed

- status: fails
- tags: SIBios,codegen,CSE
- scope: revolution/SI/SIBios
- source: session 2026-10-26

symptom: SIInterruptHandler 4 lwz InputBufferVcount[i] reloads missing in ours, 16-byte size gap
cause: unknown; our compiler CSEs the load across the || branch
fix: none: (0==v) order, nested if, (v+(x/2)), !v, x>>1 all give 108 diff lines
