# objdiff .data 0/99% with identical jump table bytes: reloc to wrong return stub

- status: works
- tags: jumptable,data
- scope: RPGol_802b7670
- source: fn_802B7888

symptom: .data <100 with identical bytes
cause: case grouping picks different return stub
fix: assemble target .s with jumptable_* renamed to @NNN, diff relocs; group cases (case 5: case 14: return;)
