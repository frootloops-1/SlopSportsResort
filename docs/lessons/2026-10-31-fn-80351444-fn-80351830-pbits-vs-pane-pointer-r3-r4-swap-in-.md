# fn_80351444/fn_80351830: pBits vs pane-pointer r3/r4 swap in unrolled bit-test loop

- status: open
- tags: regalloc,RPBow,loop
- scope: Pack/RPSports/RPBowScene/RPBow_80351444
- source: claude/sp-50f78-20261031

symptom: target mr r4,self / addi r3,ctx,0xc20; ours r3/r4 swapped (99.4 / 99.7); fn_80351830 also f0/f1 swap on table loads
cause: unknown colouring order of loop induction copy vs pBits
fix: failed: self->update(reverse,pCtx) inline (99.0), self->updatePins(&pCtx->mBits) (92.0), pBits declared at function top (flat), BowVec2 pos(pTbl[..],pTbl[..]) direct (99.6). Next: mwcc_dbg dump
