# RPBow_80320EFC lerp GPR: shift temp S outranks lbl load temp A

- status: fails
- tags: RPBow_80320EFC,regalloc,lerp,holder
- scope: fn_8032212C,fn_80320EFC

symptom: lerp i r5/d r5 vs retail r4/r3 in both lerp instances
cause: dump: A=lwz lbl (r133) generated in d stmt before S=i<<2 (r134); S colours first and takes r3; retail needs A or d before S
fix: none. Dead: d holder, accessor inline, tbl ptr, host local, d2 alias, nested/member At() (32), a local, j=i+1, ref d, 4 expr orders, else-if clamp
