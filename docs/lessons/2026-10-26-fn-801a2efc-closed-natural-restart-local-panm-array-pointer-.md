# fn_801A2EFC closed: natural restart() + local pAnm-array pointer for ONE term of end-start

- status: works
- tags: regalloc,winmgr,2EFC,steering-local,R17
- scope: Pack/RPKernel/RPSysSystemWinMgr
- source: claude

symptom: 99.5 (split reset/start) or 98.5 (natural restart, pMgr r28 vs r27)
cause: original has two pre-RA loads of the pAnm[1] slot in the unk88 statement that are merged after RA; a textually identical second load is IR-CSE'd and the extra node disappears
fix: RPSysLytAnmObj** ppAnm = pMgr->mButton[i].pAnm; unk88 = ppAnm[1]->...mEndFrame - pMgr->mButton[i].pAnm[1]->...mStartFrame (either term; ppAnm must NOT be used in unbind and must be used in exactly one term). Sweep over 7 uses: bits for reset/setPlayMode/restart/bind are free. Both terms via ppAnm, or ref/ptr used everywhere -> 99.9 (i*0x1c offset kept live in r26). Loop-top decl: never matches. MATCH-PENDING R17
