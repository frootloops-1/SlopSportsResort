# RPTns fn_80214B64: extern (incomplete-type) lbl_803C37B0 with definition moved after the function gives no change

- status: fails
- tags: rptns,fn_80214B64,vtable,extern

symptom: same 6 diff lines, 98.3%
cause: TU-local visibility of the vtable array contents is not what drives the r0/r4 choice or the addi hoist
fix: Reverted; branch claude/rptns-class-1027 keeps the class version only.
