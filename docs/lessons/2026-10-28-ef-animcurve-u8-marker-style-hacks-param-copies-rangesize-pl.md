# ef_animcurve U8 marker-style hacks (param copies, rangeSize placement) no gain

- status: fails
- tags: ef_animcurve,U8,marker,colouring,mask
- source: xfer-1028

symptom: U8 98.19: target colours pRangeTbl r30, pRandomTbl r29, loop r28 before mask r26 and rangeSize r22 last; ours colours mask r30 second, rangeSize r27 early
cause: Copies of mask/life/seed are coalesced (no change); copy of pTarget worse (97.71); rangeSize as expression temp 97.4-, declared first 98.18, int type same. Dummy-copy markers do not alter colouring here
fix: none; remaining ideas are changing mask/table use counts (spill cost = weight*(2*uses+defs)/degree) with real code, which no source form has yet provided
