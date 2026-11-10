# fn_8031A0E0 v1BC block: retail colours prove an early long-lived cos-arg (f1) and c coloured before temps

- status: open
- tags: A0E0,regalloc,scheduler,fpr
- scope: fn_8031A0E0
- source: round 8

symptom: v1BC/v1C8 block: ps_mr pair and every FPR shifted by 1-2 vs retail
cause: FPR colouring sim (lowest-free, interference from phase-0 order) on retail colours: 7 temps need a colour-1 neighbour, only possible if lfs f1,0x19c (cos arg) issues before the BC z-sub in phase 0; c must colour early (f0, shared with the v1D4.z fadds value, so c-load after stfs 0x1dc). Model: whole-V c-load + whole/worst-alias f19C load placed between the v1D4.y and v1D4.z stores in program order gives all 20 retail colours exactly. Real compiler: whole-V c alone (asm li index in another block, variant S) removes both ps_mr (harness 119, regs still shifted).
fix: Open: find natural source that (a) makes the c load and the f19C load non-disambiguable from the self stores and (b) puts the f19C read before v1D4.z += d, with c as a temp. Tools: /private/tmp/scratch-A0E0-r8/col.py, search6.py, feas.py, blk.py
