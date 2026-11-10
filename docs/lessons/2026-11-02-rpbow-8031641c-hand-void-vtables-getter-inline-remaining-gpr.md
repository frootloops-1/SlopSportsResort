# RPBow_8031641C: hand void* vtables + getter inline; remaining GPR colouring walls (new-temp coloured after inline locals)

- status: fails
- tags: regalloc,new-temp,RPBow_8031641C
- scope: RPBow_8031641C

symptom: fn_80316C7C 99.4, fn_80318EB0 99.3
cause: new-expression temps numbered after ALL inline expansions so coloured after every inline local
fix: No closure. Dead: ball read back from objs, mat declared in loop body, material accessor inline, declaring var before loop, new in inline helper, officialDb=0 before if, officialDb via inline create helper.
