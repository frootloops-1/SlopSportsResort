# extern const f32 defined before use creates extra @NNN literal

- status: works
- tags: sdata2,pool
- scope: RPTnsScene
- source: claude/rptns-3

symptom: .sdata2 doubled
cause: const propagated into fresh literal
fix: define named const floats after the functions at end of file
