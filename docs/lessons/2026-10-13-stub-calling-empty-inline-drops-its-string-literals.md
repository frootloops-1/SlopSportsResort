# Stub calling empty inline drops its string literals

- status: works
- tags: strings,rodata,testing
- scope: RPGol_802bf4f8
- source: sonnet-worker

symptom: temporary stub to test string-pool offsets emitted no strings
cause: dead inline call is removed with its literal args
fix: declare the callee extern (undefined) so strings are emitted
