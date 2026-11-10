# fn_8028DDB0: const .sdata name tables (DECL_SECTION) float their loads; sibling 1-iteration loops

- status: works
- tags: const,sdata,DECL_SECTION,fn_8028DDB0,R17,RPBsb
- scope: Pack/RPSports/RPBsbScene/RPBsb_8028d9e8
- source: wave3 2026-11-01

symptom: 91.0%: table load must sit above the previous pointer store
cause: the load floats only if the table OBJECT is const; the target keeps it in .sdata
fix: DECL_SECTION(.sdata) const char* const lbl_804BE808/80C/810[1] (R17 row 66), sibling fn_8028D7E8 shape with three for(i<1) loops; lbl_804BE810 size 8->4. Dead: static, use-site cast, struct with const member, scalar const char* globals (89.6), const char* const* locals (74.4), extern const + non-const definition (redeclaration error). Const must come from the object's qualifier
