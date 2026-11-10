# fn_8020BAAC: target keeps 3 CurPos stack temps around struct-return call; every inline spelling gives 2

- status: fails
- tags: struct-return,stack-temp,RPSports_8020b294
- source: RPSports_8020b294

symptom: frame 0xb0 vs 0xc0, stores of r3/r4 to 3 slots (0x20,0x28,0x18)
cause: MWCC elides copies of non-address-taken CurPos chains
fix: failed: t/r/pos local chain, getPos2, nested getPos3, by-value inline param, nested by-value inline, const CurPos& param, local copy in inline; all 95.5
