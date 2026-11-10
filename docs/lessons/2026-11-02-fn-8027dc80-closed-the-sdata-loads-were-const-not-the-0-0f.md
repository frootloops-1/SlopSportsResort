# fn_8027DC80 closed: the sdata loads were const, not the 0.0f

- status: works
- tags: scheduling,sdata,const,rpbsb
- scope: RPBsb_8027d3ec/fn_8027DC80
- source: claude/bsb7d3ec-1102 2026-11-02

symptom: named 0.0f const load issued before two .sdata global loads (DOL 6 bytes); every field order failed
cause: misdiagnosed: the const load was in source order; the .sdata globals' loads were held behind the preceding pointer store because they were non-const. Retail had them const
fix: extern const f32 decls at top, __declspec(section ".sdata") extern const f32 X = v; defined at TU end in address order (no [1] array needed); source order y,x,z. Diagnose by checking which loads are free vs held behind a store, not just which one moves
