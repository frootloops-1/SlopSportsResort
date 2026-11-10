# RPSports b294 owned tables and pool symbols restore all four data sections

- status: works
- tags: RPSports_8020b294,data,pool,order,symbols
- scope: Pack/RPSports/RPSportsCommon/RPSports_8020b294
- source: codex-b294-complete-1104

symptom: Unit 27/41 exact with rodata 5.8%, data 0%, sdata2 40%; source only declared most owned resources extern.
cause: Missing owned message and layout tables; merged color and padded float target symbols; incorrect function emission order.
fix: Define message tables and the exact string blob, writable name and pane tables, explicit referenced wide-text pool, color bytes and scalar; synchronize target symbols from verified same-address bytes; reorder target functions. All four data sections 100%, 29/41 exact, no regressions, not a full match.
