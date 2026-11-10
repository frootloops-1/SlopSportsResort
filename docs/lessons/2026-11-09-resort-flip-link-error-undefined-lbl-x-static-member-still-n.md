# resort: flip link error 'undefined lbl_X' = static member still named lbl_ in symbols.txt

- status: works
- tags: resort,flip,symbols,RPGrpRenderer
- scope: resort
- source: rp9b-renderer

symptom: flip_gate link fails: undefined lbl_806F4E04
cause: RPGrpRenderer::spCurrent kept its placeholder lbl_ name; extra weak copies in our object did not affect the DOL
fix: rename to the mangled static member name (spCurrent__13RPGrpRenderer); flip then blocked only by real code diffs
