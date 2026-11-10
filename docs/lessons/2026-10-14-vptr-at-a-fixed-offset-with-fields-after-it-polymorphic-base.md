# vptr at a fixed offset with fields after it: polymorphic base class

- status: works
- tags: vtable,layout
- scope: RPTns_8022a17c

symptom: vptr expected at 0x78, got 0x8C
cause: MWCC places the vptr after the class's own data members
fix: base {u8 _00[0x78]; virtuals}, later fields in a derived class
