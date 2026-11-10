# Literal vs defined char array at pool base changes callee-saved reuse in inline arg

- status: works
- tags: rodata,string,stringBase0,inline,RPSports
- scope: Pack/RPSports/RPSportsCommon/RPSports_801ecc00

symptom: Replacing SpPlayStream("STRM...") with a defined const char lbl_X[56] array (to own a dtk lbl_ string pool) dropped fn_801ECD64 100->91.7: array address rematerialised (addi r4,r30) instead of held in r30 (mr r4,r30)
cause: dtk lbl_ over a merged string pool is just @stringBase0; the original used literals
fix: keep string literals in each fn (pool order = codegen order, fix emission order first), rename symbols.txt lbl_X -> @stringBase0 scope:local data:string_table with size = string bytes only (0x36 of 0x38); RPSports_801ecc00 rodata 58->100
