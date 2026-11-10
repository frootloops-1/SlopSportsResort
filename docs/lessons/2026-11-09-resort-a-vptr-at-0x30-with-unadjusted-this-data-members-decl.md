# resort: a vptr at +0x30 with unadjusted this = data members declared before the first virtual

- status: works
- tags: resort,vtable,layout,savedatamgr

symptom: lwz r12,0x30(r3) virtual call modelled as a raw vtable-array cast
cause: Class declares data members before its first virtual function
fix: Model the class members-first (RPSysSysMsgWinMgr.h Unk_80271E70); showErrorWindow 99.8->100
