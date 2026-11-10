# fn_80313F60: named local read once is copy-propagated; two reads give exact regs but add a branch

- status: open
- tags: regalloc,copy-propagation,RPBow_80313028,vreg-order
- scope: RPBow_80313028

symptom: const 1 colours r4 and w8 reload r0 (target: 1 in r0, reload in r3); 99.7%
cause: stb li merges into stw li (vreg 48) numbered below the w8 reload temp (vreg 50); frontend copy-propagates any single-read named local back to a temp
fix: Open. Reload held in function-level i read twice (else if (i != 0), or i==0 && i==0) gives exact target registers, leaving one extra beq/bne (98.8). Dropped by frontend, no change: (void)i, i=i, i-i, i==i, empty if(i){}, dead copy, label, i=0 in else. Worse: i|1 96.5, i==0||i==0 97.4, store in both branches 90.5. Need a free second read or two compares that merge to one cmp/branch.
