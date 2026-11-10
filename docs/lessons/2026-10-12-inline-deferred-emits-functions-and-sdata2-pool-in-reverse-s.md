# -inline deferred emits functions and sdata2 pool in reverse source order

- status: works
- tags: mwcc,inline-deferred,sdata2,function-order,layout
- scope: RP units

symptom: objdiff 100% per function but linked DOL differs; text order or .sdata2 constant order wrong
cause: RP units compile with -inline deferred; MWCC emits .text and creates pool constants in reverse of definition order
fix: define functions in reverse address order (forward-declare callees as needed)
