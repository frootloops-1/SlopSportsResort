# MWCC drops a dead base vtable store unless a const-object load sits between it and the next vptr store

- status: open
- tags: 801f1d4c,ctor,vtable,dse,const
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f1d4c
- source: ctor-20261031

symptom: target keeps the inlined base ctor's vptr store (lbl_803C2CF0) in some derived ctors (2430, 2FB4, SpSceneNode in 63CC) and not in others (27E8, 3D5C, 44C4)
cause: global/non-const loads in the derived body do not keep it; a load from a TU-defined const object (const char* const tbl[]) is hoisted between the base stores and keeps it (bisected in scratch); SpSceneNode inline at a new-site keeps it with no visible load
fix: 2FB4: DECL_SECTION(".data") const char* const lbl_803C29F8 + *(const char**)& for the second read (86.8 -> 98.5, MATCH-PENDING). Original mechanism unknown
