# Pool order: static inline with literals + dead anchor fn last in source; ctor mulli via Entry::reset inner loop

- status: works
- tags: string-pool,sdata2-order,anchor,mulli,ctor
- scope: Pack/RPKernel/RPSysPauseMenu

symptom: strings/double pooled after first-address user; ctor 74.6
cause: pool order follows compile order (reverse source); loop forms fold mulli
fix: unreferenced static anchor fn last in source calling the inline with literals and doing int->float conversion (linker strips it); Entry::reset() with inner for(j<N) + for(int i) mEntries[(u8)i].reset()
