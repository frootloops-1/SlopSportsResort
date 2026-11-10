# RPBox_803024c0 .data is 3 trivial vtables {0,0,~T}; member-class model emits them but loses ctor match

- status: open
- tags: RPBox_803024c0,vtable,data,placement-new
- scope: RPBox_803024c0

symptom: .data 0%: ours has no vtables (hand-written fn_80303D24/CE4/CA4 deleting-dtor externs + extern char vtable refs)
cause: original .data = lbl_803C9BD0/DC/E8, each {0,0,dtor}; a class with only 'virtual ~T(){}' makes MWCC emit exactly that. Placement-new of the member adds an addic./beq null check; real member ctors in BoxMain::BoxMain(u8*) (symbol renamed __ct__7BoxMainFPUc) drop the check (ctor 99.2%) but run in declaration order (0x18C, 0x274, then body 0x168), original stores 0x274, 0x168, 0x16C, 0x18C. Vtable emit order came out E8,DC,D0 (orig D0,DC,E8) and dtor text order DC,D0,E8 (orig E8,DC,D0).
fix: unsolved: needs a source shape that constructs the 0x274 vptr first and fixes weak emission order; unit also has code residue in fn_803024C0 (94.7) and fn_8030264C (90.5), so no flip even if .data lands. Experiment left uncommitted in /private/tmp/ogws-boxdata-1028 (branch claude/boxdata-1028)
