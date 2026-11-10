# Tail padding and BSS rounding make most data sections look inexact

- status: works
- tags: data,bss,sbss,padding,tooling
- source: tools/data_diff.py 2026-10-15

symptom: data_diff.py: 336 .data/.rodata/.sdata/.sdata2/BSS sections 1-7 bytes smaller in ours
cause: dtk splits include trailing alignment padding (and round .bss/.sbss up to section alignment); our objects are the raw sum of objects and the linker adds the pad
fix: Not a bug. data_diff.py classes it TAIL. Together with STRAY this takes 462 inexact units down to 122 with real data mismatches
