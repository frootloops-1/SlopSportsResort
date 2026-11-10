# View-struct field still CSEd across loop; make it a real member of self's type

- status: works
- tags: cse,offset,view-struct,mwcc
- source: RPBox_802cf93c 2026-10-23

symptom: addi rX,self,0x1A8 hoisted into extra saved reg (savegpr_27, frame +0x10) when the same sub-matrix is used before and inside a loop
cause: address via cast view struct ((V*)self)->m is CSEd like pointer arithmetic; direct base-class member arrays (self->m108) are not
fix: declare a per-class struct BoxHd : BoxObjHead with the fields as real members and take BoxHd* self (fn_802D5F08 92.1->99.0)
