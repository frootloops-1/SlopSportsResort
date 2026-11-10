# sdata2 const array emitted before pooled literals

- status: open
- tags: sdata2,literals,pool
- scope: RPGol_802b66c4
- source: sonnet-worker

symptom: 'ABCD' array lbl_804C4900 lands at offset 0; orig double first
cause: named const data precedes the literal pool
fix: untested with all users present; function-local static same order and renames symbol
