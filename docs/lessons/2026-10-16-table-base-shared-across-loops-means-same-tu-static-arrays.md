# table base shared across loops means same-TU static arrays

- status: works
- tags: data,anchor,static,rpbsb
- source: RPBsb_8028c450 2026-10-16

symptom: original addi rP,rBase,0/0x20/0x3C off one base for several name tables
cause: MWCC section-anchor addressing (...data.0) only for TU-static arrays
fix: split into one global + static arrays; DOL byte-identical though objdiff shows reloc name ...data.0 vs lbl_ (99.8)
