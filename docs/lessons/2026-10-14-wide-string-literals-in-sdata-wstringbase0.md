# Wide string literals in .sdata: @wstringBase0

- status: works
- tags: wstring,sdata,symbols
- scope: RPTns_80248bb8
- source: claude 2026-10-14

symptom: .sdata 82%: target lbl_ size 7 for a UTF-16 string
cause: MWCC pools wide literals into @wstringBase0 (incl. 2-byte terminators)
fix: rename symbols.txt entry to @wstringBase0 scope:local with the object's size (RPTns_80248bb8 0xA)
