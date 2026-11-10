# LoadScnLightInner: loop-variant base (loop-carried re-copy) selects offset induction

- status: works
- tags: loop,induction,iro,R17,egg
- scope: egg/gfxe/eggLightManager
- source: step2 2026-11-01

symptom: 99.6%: clear loop used pointer induction, retail uses offset induction with ctr
cause: IRO picks offset (not pointer) induction for base->arr[i] when the base is loop-variant; diagnostic: a base from a global changed in the loop gave the exact regs plus ctr
fix: ResLightSet set = lightSet before the loop, set = lightSet at the end of each pass (R17 row 64). Dead: if/else idx, const ref alias (96.4), store per arm (91.6), static inline index helper (pointer induction), for(;;) with top break (exact regs but no ctr, 98.6), new named pSet (shifts saved regs r24-r28)
