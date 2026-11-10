# Empty static initializer: .ctors entry via section(.ctors) fn pointer + force_active; vptr at +N with this==obj via padded base

- status: works
- tags: ctors,sinit,virtual,loop
- source: RPBsb_80289acc

symptom: .ctors entry pointing to plain blr; virtual call with vtable at 0x28 but r3 unchanged; loop ptr/counter reg swap
cause: n/a
fix: extern C void fn(void){} + #pragma force_active on + __declspec(section ".ctors") static void(*p)(void)=fn; dummy virtual struct derived from non-polymorphic base u8 pad[N]; declare loop-body pointer before the for; bind q=objs[i] local
