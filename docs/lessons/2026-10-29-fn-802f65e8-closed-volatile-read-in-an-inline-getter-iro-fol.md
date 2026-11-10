# fn_802F65E8 closed: volatile read in an inline getter (IRO fold blocked + late vreg), and Coloring_SimplifyGraph model (threshold 29)

- status: works
- tags: RPBox_802f5a6c,regalloc,IRO,volatile,inline-getter,coloring
- scope: all

symptom: 98.5% variants: volatile named local fixes volatile regs but callee-saved order rotates (loop offset coloured last)
cause: Backend colouring = Coloring_SimplifyGraph: sweep ascending vreg number, push nodes with degree<29 and decrement neighbours immediately, colour in reverse push order. A surviving level temp numbered below the loop offset and low degree is removed early, dropping the offset below 29 so it is pushed first (coloured last). Reproduced exactly with a Python port over regalloc-gpr-pass-1-all.txt neighbour lists at K=29.
fix: static inline s32 BoxElemLevel(BoxElem* e){return *(volatile s32*)&e->level;} then 's32 level = BoxElemLevel(elem);' : volatile blocks IroPropagate folding, inline getter gives the vreg a late number. 10/10, DOL 0, R17 marker + ledger row. General recipe: dump with mwcc_dbg, simulate K=29 sweep from the 'all' file to see which vreg number shifts flip a node's removal sweep.
