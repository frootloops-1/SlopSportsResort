# Deleting dtor with +0x50 member: extern C double-nested ifs

- status: works
- tags: RPGolFieldManager,dtor

symptom: C++ class dtor gives virtual call or -1 flag (72.9-80.5%)
cause: CW emits addic./beq/beq from doubled null checks
fix: extern C fn; sub=(u8*)self+0x50 after outer check; if(sub){if(sub)dt} and if(self){if(self)dt}
