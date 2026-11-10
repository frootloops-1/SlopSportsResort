# fn_802BEE50 layout reload hoisted above stores

- status: open
- tags: golf,scheduling
- scope: RPGol_802bca94
- source: sonnet-worker

symptom: 93.1: orig loads 0xC(r31) after idx store
cause: unknown aliasing/scheduling
fix: failed: idx type bool/char/s8/u16
