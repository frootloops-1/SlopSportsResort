# fn_80246254 RPTns_80244198 remaining colouring wall: msg/msg2 must colour before loop counters

- status: open
- tags: RPTns,fn_80246254,regalloc,mwcc_dbg
- scope: Pack/RPSports/RPTnsScene/RPTns_80244198

symptom: target msg=r29 msg2=r28 active=r26 push=r25 n=r29 off=r28; ours msg=r26 msg2=r27 active=r28 n=r25
cause: mwcc_dbg: colouring order ~descending vreg, picks lowest already-used non-conflicting nonvolatile; target colours msg/msg2 before the loop counters
fix: open: decl-order perms of i/msg/msg2/active/push no change; hoist off/n to top 68->66 lines no score change; separate loop var for text loop worse; regsearch generic 10 min no gain
