# resort bowling: namespaced .bss objects need mangled names and C++ struct size

- status: works
- tags: resort,bowling

symptom: bss symbol mismatch
cause: symbols.txt used lbl_ and aligned split size
fix: gBackgroundNpcParams__7Bowling, size 0x44 (struct) not 0x48 (split)
