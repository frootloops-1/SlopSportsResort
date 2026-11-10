# fn_802C0C50: void* param + cast local gives arg its own vreg; int accessor makes n the top temp: rotation fixed, 134 -> 8 diff lines (R17, ledger 39)

- status: works
- tags: rpgol,802c0c50,vreg,param-cast,accessor,colouring,r17
- source: worker iro-0c50 2026-10-31

symptom: 99.3%, 134 lines: self r30/n r25/arg r31 vs target self r31/n r30/arg r25
cause: a typed parameter keeps its parameter vreg (33) and is coloured first; a plain copy, const& or one-field holder is removed by the optimizer before vregs are numbered; a cast through a different type (void*, u32, int) survives as a named local (vreg 47/48, sweep 2)
fix: void fn(Self*, void* arg) { GolScoreArg* a = (GolScoreArg*)arg; ... n = a->getNumPlayers(); } with int getNumPlayers() const accessor; cast alone 99.2. Left: r0/r3 swap of score lbz (vreg 153) vs pane-flag lbz 0xB7 (154) in the inner card loop, flag coloured first; needs flag load created before the score load while the score load stays before the flag store. Dead: sum after SetVisible (98.3), nested SetBit, single-expression, if form, u8/int/u32 flag local, u8* pBits, sum = x + sum, comma in SetVisible arg, tb pane local (99.0), getScore accessor. permute.py setup_cxx fails with ModuleNotFoundError: src.
