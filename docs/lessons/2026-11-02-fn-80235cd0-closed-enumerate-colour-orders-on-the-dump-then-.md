# fn_80235CD0 closed: enumerate colour orders on the dump, then build them (getter return temp + CSE'd duplicate expr)

- status: works
- tags: fn_80235CD0,RPTns_80235cd0,regalloc,color_sim,mwcc_dbg
- scope: RPTns_80235cd0

symptom: 99.2 GPR colouring wall: named other r30 vs r28, loop 3/4 e/s/offset regs rotated
cause: Named locals are coloured last (or first if deg>=29 -> sweep 2); target needed other coloured after the loop offsets and loop s values coloured before them, i.e. s = inline-return @ temps in source order and other = an IRO CSE temp
fix: TnsSub* s = TnsGetSub(e) (static inline return e->p38) in loops 3/4 + spell loop 4's switch st->score[side ^ 1] while keeping int other = side ^ 1 for switch 1 (IRO CSE replaces other by a late temp). 100%, R17 marker ledger 79. Method: replay colouring on the mwcc_dbg graph (colour = lowest used free callee-saved, else new from r31 down) and brute-force which orders/numberings give the target before editing source
