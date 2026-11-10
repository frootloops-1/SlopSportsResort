# MWCC string pool order: data initializer literals first, then fn literals by codegen order

- status: works
- tags: strings,pool-order
- scope: RPGol_802b020c
- source: RPGol_802b020c

symptom: pool order differs
cause: parse-time initializer literals come first
fix: define .sdata/.data char* initializers in the TU; unreferenced strings: static non-const char* array after the vtable (adds .data bytes, open)
