# resort: read struct layouts off MWCC member-wise copies (RPSportsPlayerData 0xDF4, SystemData 0x82AC)

- status: works
- tags: resort,layout,struct-copy,RPSportsPlayerData
- scope: resort
- source: RP batch 5 (2026-11-09)

symptom: SaveDataMgr accessors copying sports data didn't match ogws layouts
cause: MWCC copies non-POD structs member by member (scalars singly, arrays as lwzu loops)
fix: derive field offsets/array counts from the copy loops; 6 accessors exact first try
