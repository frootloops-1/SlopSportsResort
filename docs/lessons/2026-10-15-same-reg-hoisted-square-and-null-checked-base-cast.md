# Same-reg hoisted square and null-checked base cast

- status: works
- tags: mwcc,regalloc,cast
- scope: RPTns_8023c74c
- source: claude/rptns-2

symptom: fmuls f10,f10,f10 vs ours f10,f0,f0; mr r4,r30;beq;addi r4,r30,0x44
cause: constant squared in place; implicit derived->base pointer conversion
fix: f32 r2=34.0f; r2*=r2; and void* cb=self; if(self) cb=&self->cbvt;
