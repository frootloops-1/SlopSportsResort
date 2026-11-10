# resort: verify.py showed 0/0 fns: objdiff-cli 3.6 JSON has no 'kind' field

- status: works
- tags: resort,tools,verify,objdiff
- source: 2026-11-09

symptom: verify.py prints 0/0 fns exact for every unit
cause: symbols lack kind:SYMBOL_FUNCTION in objdiff-cli 3.6.1 output
fix: treat symbols with 'instructions' as functions (fixed in tools/verify.py)
