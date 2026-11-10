# 4 sda21 colour byte loads: four separate extern const u8 symbols defined at file end

- status: works
- tags: sdata2,color
- scope: RPGol_802aaf88
- source: fn_802AB144

symptom: li+offset or li 0xff
cause: struct/array or visible initializer
fix: four extern const u8 decls before use, definitions at end of file
