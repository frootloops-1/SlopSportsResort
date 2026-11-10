# Statics referenced from other units need global lbl_ names (link: undefined lbl_804BF8D8)

- status: works
- tags: rpgolmath,link,static,matching
- scope: RPGolMath
- source: orchestrator

symptom: Matching flip fails to link: undefined lbl_804BF8D8 referenced from RPGolScene_unsplit
cause: file-static objects get local symbols
fix: declare them non-static in extern C with the symbols.txt name; DOL sha then OK
