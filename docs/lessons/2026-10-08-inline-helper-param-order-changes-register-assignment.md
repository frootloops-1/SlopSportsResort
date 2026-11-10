# Inline helper param order changes register assignment

- status: works
- tags: regalloc,inline,params
- scope: Pack/RPSports/RPSportsCommon/RPSysNunchukCheckScene/Calculate

symptom: anm/pane regs r25/r26 swapped in unbind/forceBind sequences (98.97%)
cause: inline parameter copies are coloured by parameter order
fix: playAnm(Pane*, AnmObj*), setAnmFrame(Pane*, AnmObj*, s16), playWait(Pane*, AnmObj*) wrapper setting timer -> 100
