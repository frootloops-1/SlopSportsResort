# RPBow_80320EFC: lerp-loop count loaded twice = const int[1] array; scalar const int defined at file end fixes it

- status: works
- tags: RPBow_80320EFC,fn_80320EFC,licm,const-int,sdata2,hoist
- scope: unit

symptom: loop preheader loads the same .sdata2 count twice (lwz r3 for hoisted n-1, lwz r31 for later CSE); target loads once into r31 and does subi r28,r31,1
cause: count declared as const int lbl[1] (array element load); LICM hoists lbl[0]-1 with its own load copy
fix: extern const int lbl_804C5DC8; uses read the scalar; definition const int lbl_804C5DC8 = 16; placed at END of the file (visible init before use would fold). 98.6->99.1, size 4120->4112, .sdata2 layout unchanged; n7 helper-param local no longer needed
