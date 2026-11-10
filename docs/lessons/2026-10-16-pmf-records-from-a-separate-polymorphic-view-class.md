# PMF records from a separate polymorphic view class

- status: works
- tags: ptmf,vptr,rpbsb
- source: RPBsb_8027039c 2026-10-16

symptom: compiler emits its own __vt__ store
cause: real class declared polymorphic
fix: keep the real class non-polymorphic, store vptr manually in the data-base ctor; take &View::vfXX from a view class with vptr at 0x28
