# Unit 100% but DOL fails: check emitted function order

- status: works
- tags: dol,order,objdiff
- scope: RPTns_80240454
- source: claude 2026-10-14

symptom: objdiff all-100 yet main.dol FAILED; later functions shifted
cause: objdiff pairs by symbol, ignoring .text order; source order (reversed) misplaced one fn
fix: compare nm -n order with the asm; fix source order (RPTns_80240454 AF8/B04)
