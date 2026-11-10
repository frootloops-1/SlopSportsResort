# Virtual call through obj+8 vptr: non-polymorphic 8-byte base then virtual struct

- status: works
- tags: vtable,vptr-offset,virtual
- scope: RPTns_802318a4
- source: claude/rptns-2

symptom: asm loads vtable from 0x8(obj) (lwz r12,0x8(r3); lwz r12,0x10(r12)) while a plain virtual struct gives 0x0(r3)
cause: object has a non-polymorphic 8 byte prefix; MWCC places the vptr after a non-polymorphic base
fix: struct Base{u8 pad[8];}; struct P : Base { virtual void v0(); virtual void v1(); virtual void v2(); }; p->v2() gives vptr at 0x8, slot 0x10
