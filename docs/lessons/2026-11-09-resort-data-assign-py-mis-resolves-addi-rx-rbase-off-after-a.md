# resort: data_assign.py mis-resolves addi rX,rBase,off after a lis/addi base

- status: open
- tags: resort,tools,data
- scope: resort
- source: can-fld

symptom: data assigned to the wrong unit (0x8068xxxx+off without the @l)
cause: all_refs reconstructs base+offset incorrectly
fix: workaround: assign by label references from the asm; fix tools/data_assign.py all_refs
