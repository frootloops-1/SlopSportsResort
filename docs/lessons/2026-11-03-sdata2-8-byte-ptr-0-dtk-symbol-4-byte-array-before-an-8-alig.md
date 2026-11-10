# sdata2 8-byte {ptr,0} dtk symbol = 4-byte array before an 8-aligned const char*[2] local initializer

- status: works
- tags: sdata2,alignment,aggregate,symbols,RPSports_801ffec0
- scope: Pack/RPSports
- source: claude/sp801ff-1103

symptom: dtk lbl_ size 8 holding one pointer and a zero word, next symbols 4+4 bytes
cause: MWCC 8-aligns an 8-byte local aggregate initializer (const char* names[2]) in .sdata2; a preceding 1-element array leaves a 4-byte pad. Also _GXColor c = {255,255,255,alpha} makes a 4-byte sdata2 object at parse time (dtk shows three 1-byte lbls + gap)
fix: define the arrays as local initializers in source (parse order = pool order) and merge/resize the dtk symbols to the compiler objects (@N scope:local)
