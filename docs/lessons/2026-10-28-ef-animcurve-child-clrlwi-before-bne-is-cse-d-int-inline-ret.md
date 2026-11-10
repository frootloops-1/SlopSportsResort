# ef_animcurve Child: clrlwi before bne is CSE'd int inline-return temp

- status: fails
- tags: ef_animcurve,schedule,inline-return
- scope: nw4r/ef/ef_animcurve
- source: claude/ac-*-1028

symptom: target clrlwi r3,r25,16 before loop0==loop1 bne; ours after
cause: (int)frame1 temp from an int-returning inline, CSE'd at the join; frame1 shares inner frame reg
fix: dead: int return both 94.7; template int return 2nd call only 97.3 (opcodes fixed, frame1 takes ret reg); frame1==frame0 order; multi-return inline (identical); multi-return+int 96.2/92.6; loop=0 inside inline (regression). Target saved regs are clean first-def order (pHeader r31..pKeys r23, params r22-r18); ours colours pKeys first -> suspect extra interference, not decl order
