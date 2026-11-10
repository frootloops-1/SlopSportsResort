# Struct copy via getter by const-ref set() halves temps: fn_801C9E7C 89 -> 100

- status: works
- tags: mwcc,struct-copy,frame
- source: RPUtl_801C9E7C

symptom: frame 0x90 too big; two Descriptor copies where target has one
cause: set(Descriptor value) by value plus getPending() return temp = 2 copies
fix: set(const Descriptor&) and keep getPending() call; plus float pair with user copy ctor (nw4r::lyt::Size-like) so implicit copy uses lfs/stfs
