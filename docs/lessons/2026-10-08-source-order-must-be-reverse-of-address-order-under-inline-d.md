# Source order must be reverse of address order under -inline deferred

- status: works
- tags: mwcc,order,string-pool

symptom: string pool / .text order differs; 94.9-95.3% on string-using fns
cause: -inline deferred without defer_codegen off emits .text and pooled strings in reverse source order
fix: write functions in reverse address order (do not use defer_codegen off: stops header inlines)
