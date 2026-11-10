# Virtual call through r12 twice needs a real C++ virtual, not a fn-pointer vtable struct

- status: works
- tags: regalloc,virtual,vtable,r12
- scope: RPSports_80209a58
- source: claude nearmiss 2026-10-15

symptom: orig lwz r12,0x68(r3); lwz r12,0x58(r12); ours lwz r6/r5 for the vtable then r12 (fn_80209A58 99.4, fn_80209ABC 98.9)
cause: hand-rolled vtable struct / fn-pointer cast loads vptr into an ordinary temp; MWCC real virtual dispatch keeps vptr and slot in r12
fix: declare a class with virtuals (vptr at +0x68 via a padding base; slot offset = 8 + 4*index) and call obj->vfNN(...); also use the extern sdata2 label for the 0.0f compare literal (reloc)
