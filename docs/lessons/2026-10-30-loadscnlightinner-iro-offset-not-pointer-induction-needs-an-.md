# LoadScnLightInner: IRO offset (not pointer) induction needs an extra loop exit/skip before the access

- status: open
- tags: regalloc,LightManager,induction,IRO,loop,egg
- scope: egg/gfxe/eggLightManager

symptom: clear loop: backend counter coloured first (offset r3) vs retail offset r5/pp r4/obj r3
cause: IRO strength-reduces loop 1 to a rotated, guarded POINTER induction unless the loop has an extra exit/skip path before the access; with one it keeps an OFFSET induction (low vreg) = retail regs
fix: pSet->lightId[i] ternary + 'if (i >= lightNum) break;' at body top -> exact regs and ctr loop but one leftover cmplw/bge (98.7); 'if (i==5) continue;' at top also gives exact regs. Folded-early conds (if(0), skip|=0), continue after access, goto/while/do-while, if/else, a call in the body: still pointer. Need a zero-code exit
