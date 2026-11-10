# Virtual call through vptr at a nonzero offset

- status: works
- tags: virtual,vptr,vtable,layout
- scope: RPGol_802c6e28
- source: claude/rpgolscene-unsplit

symptom: lwz r12,0x68(r3); lwz r12,0x58(r12); bctrl with r3 unadjusted
cause: class whose vptr sits at +0x68 (non-polymorphic base of 0x68 bytes)
fix: pad base struct of 0x68 bytes + derived class with filler virtuals so slot offset = 8+4*idx; fn-pointer casts put the vptr in the wrong reg
