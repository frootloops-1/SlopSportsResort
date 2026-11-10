# DOL mismatch on flip: check section SIZE words and r13-offset diffs first (sbss gap); weak dup data is deduped by the linker

- status: works
- tags: DOL,flip,sbss,r13,size,dead-strip,layout,RPGrpRenderer
- scope: RPGrpRenderer
- source: opus worker, verified 2026-10-12

symptom: ~4600 DOL byte diffs after flipping an object though all code exact
cause: Weak vtable/policyTable copies are deduped and harmless; the real cause was .sbss 8 bytes short (lbl_804BF620 4B instead of 8B), shifting every r13-relative offset; size word at DOL header 0x800064bc differs (0x1028 vs 0x1030)
fix: Make the referenced neighbour larger (RPGrpCamera* lbl_804BF620[2]); an unreferenced padding global is dead-stripped. Diagnose with cmp -l and look at whether diffs are +/-8 in r13 offsets
