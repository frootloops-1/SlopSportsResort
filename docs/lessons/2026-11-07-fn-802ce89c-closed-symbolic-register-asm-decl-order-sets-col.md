# fn_802CE89C closed: symbolic-register asm, decl order sets colour

- status: works
- tags: RPBox,asm,regalloc,colour,R17
- scope: Pack/RPSports/RPBoxScene/RPBox_802cb9cc

symptom: two-register colour swap (r5/r6) on plain loads that no C spelling moves
cause: symbolic-register asm locals are scheduled with C code; their colour follows declaration order. Naming a PHYSICAL register in inline asm removes it from allocation for the whole function (total reshuffle); .scheduling off breaks interleave
fix: declare register locals in desired colour order, load them with symbolic asm (asm { lwz m, sym }) without .scheduling off
