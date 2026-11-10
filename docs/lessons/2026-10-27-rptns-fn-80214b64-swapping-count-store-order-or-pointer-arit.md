# RPTns fn_80214B64: swapping count store order or pointer-arithmetic for lbl[9] gives no gain

- status: fails
- tags: RPTns_80214480,fn_80214B64,scheduling
- scope: RPTns_80214480

symptom: Remaining diff: count 6 in r4 not r0; addi r0,r3,0x24 scheduled before the +0x44 store
cause: Scheduler hoists the &lbl_803C37B0[9] addi above the +0x44 store, which takes r0 and pushes the constant to r4. Swapping count stores costs .text; (u8*)lbl+0x24 is identical
fix: No source change kept; open hypothesis is authentic temporary lifetime of the secondary vtable address
