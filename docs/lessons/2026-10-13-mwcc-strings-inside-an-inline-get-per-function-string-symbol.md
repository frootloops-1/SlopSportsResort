# MWCC: strings inside an inline get per-function @STRING@ symbols; pool order is reverse source order

- status: works
- tags: pausemenu,string-pool,inline,str-pool
- scope: Pack/RPKernel/RPSysPauseMenu

symptom: base+offset string pairs appear twice in original
cause: inline helpers with string literals get per-function string symbols
fix: write the block out twice/macro instead of inline helper; local 's32 player = mUNK_0x80;' before switch fixed 1130 95->99.6; 'u8 result=3' declared after first if block
