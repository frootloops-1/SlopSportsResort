# vptr-first view needs explicit pad when next field at +8

- status: works
- tags: struct,vptr,regalloc,rpbsb
- source: RPBsb_8026eccc 2026-10-16

symptom: r30/r31 swaps in several fns
cause: field offset off by 4
fix: add u32 pad04 after the vptr
