# fn_8022A17C LCG + parity prologue allocation (93.0)

- status: open
- tags: regalloc,lcg
- scope: RPTns_8022a17c

symptom: orig const r6, count r0, cmpwi 1+bne; ours const r0, count r8, clrlwi.+beq
cause: unknown
fix: failed: decl order, seed temp forms, Random member fn, switch on count&1, s32/int/u32 odd temps, bool ok=rnd==3; best bool odd=(count&1)==1 before rand16()
