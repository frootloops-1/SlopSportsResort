# fn_801CA3DC round 2: real nw4r::lyt::Pane accessors and memcpy copy do not fix set(pane) scheduling

- status: fails
- tags: mwcc,scheduling,mtx-copy,wall,fn_801C8A08
- source: RPUtl_801C9E7C

symptom: same set(pane) wall as RPUtlLytFrameCursor fn_801C8A08
cause: unknown; accessor form compiles to identical IR
fix: failed: nw4r::lyt::Pane GetName/GetSize/GetGlobalMtx/GetBasePositionH/V with scalar locals (identical 90.3, and full nw4r headers bring back OSFastCast .text), Size by value (stack slot), const Size& (74.9), memcpy (call, 56.4), __memcpy (identical)
