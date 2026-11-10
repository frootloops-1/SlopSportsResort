# fn_801A2EFC: RPSysFrameCtrl& local for reset();start() regresses 99.5 -> 98.5

- status: fails
- tags: fn_801A2EFC,RPSysSystemWinMgr,register,inline
- scope: RPSysSystemWinMgr
- source: session 2026-10-26

symptom: 4 extra 'lwz r3,0x20(r28)' before sth 6(r3) in each inlined UpdateButtonAnm copy
cause: A named FrameCtrl& local coalesces like restart(): pMgr is colored r28 (98.5%), same as the unsplit restart() form
fix: unsolved; kept reset();start() split (4 lines). Data sections of this unit are already 100%, only this function blocks flipping to Matching
