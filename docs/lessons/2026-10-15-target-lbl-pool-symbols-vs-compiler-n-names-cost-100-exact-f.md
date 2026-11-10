# Target lbl_ pool symbols vs compiler @N names cost 100+ exact functions; rename in symbols.txt

- status: works
- tags: data,symbols,config,objdiff,reloc,sdata2
- source: tools/pool_renames.py 2026-10-15

symptom: functions with correct code score 99.x% because relocations to pooled constants/strings name lbl_XXXXXXXX on the target side and @N on ours (near_miss.py DATA-REF:pool/hidden)
cause: objdiff matches relocation targets by name; dtk names unnamed data lbl_, our compiler names pool entries @N / @stringBase0; adjacent byte-referenced constants (GXColor) were also split into four 1B lbl_ symbols
fix: tools/pool_renames.py pairs relocs of identical functions, requires equal addend and identical bytes, and renames lbl_ to @N with scope:local (the convention already used for 1792 symbols). 492 renames gave +106 exact functions in 41 units, 0 regressions. Merge runs of consecutive 1B lbl_ symbols into one 4B symbol first so addends line up
