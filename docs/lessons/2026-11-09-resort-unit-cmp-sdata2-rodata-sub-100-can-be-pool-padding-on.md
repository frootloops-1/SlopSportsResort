# resort: unit_cmp sdata2/rodata sub-100 can be pool padding only

- status: works
- tags: resort,bowling,data,flip

symptom: unit_cmp shows .rodata size mismatch
cause: compiler pads pool objects differently from symbols.txt sizes
fix: run flip_gate before chasing; it is the authority
