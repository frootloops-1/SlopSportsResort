# Object scores 100% code/data but flipping to Matching breaks the DOL: check function order, bss order, force_active

- status: works
- tags: matching,dol,order,bss,force_active
- scope: MetroTRK,revolution/VF,RPGolScene

symptom: objdiff 100% yet DOL SHA1 differs after flipping NonMatching->Matching (usr_put, mslsupp, nand_drv, RPGol_802bb044, targsupp)
cause: objdiff matches by name: MWCC emits fns/vars in reverse source order for some shapes so linked order differs; unreferenced stub fns are dead-stripped unless force_active; wrong function pointer target (VFi_NANDPrivateOpen vs VFi_NandOpen) shows only as DOL byte
fix: tools/order_check.py lists units whose .text symbol order differs; swap definitions (reverse of target order); swap bss decl order (nm -n both .o); add force_active in symbols.txt for unreferenced asm stubs; tools/dol_diff.py (maps differing DOL bytes to symbols) finds the rest
