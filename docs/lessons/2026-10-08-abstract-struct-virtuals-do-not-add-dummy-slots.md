# Abstract struct virtuals: do not add dummy slots

- status: works
- tags: mwcc,vtable,abstract

symptom: lwz r12,0x10/0x1c instead of 0x8/0x14 for a virtual call through a local abstract struct
cause: dummy leading virtuals shift slots
fix: first declared virtual is real slot 0x8; real 0x14 is the fourth declared
