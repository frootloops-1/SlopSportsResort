# fn_80239BB0: inline-returned array loads close a<->col*4 induction GPR swap

- status: works
- tags: RPTnsScene,regalloc,colour,inline,induction,mwcc_dbg
- scope: Pack/RPSports/RPTnsScene/RPTns_802390b0

symptom: callee-saved swap: target a=r25 o=r24 col*4 induction=r23; ours a=r23, induction r25 (40320-perm decl search had failed)
cause: mwcc_dbg: induction @temp (r52) coloured before named locals o/a; named locals can never beat it
fix: static inline TnsBrick* TnsBrickAt(TnsBrickSet*, int) for both a = ...arr[i] and o = ...arr[row*80+col] -> 100 (a only: 99.9, o/induction swap left). MATCH-PENDING R17 + ledger row
