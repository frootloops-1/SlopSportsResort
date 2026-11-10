# fn_802926EC: stB colouring order proven by mwcc_dbg; 5 more shapes dead

- status: fails
- tags: fn_802926EC,colouring,bool,RPGol,mwcc_dbg
- scope: Pack/RPSports/RPGolScene/RPGolFieldManager
- source: golfield-1102

symptom: 99.8% 24 lines: stB r27 (target r3), 8D0 ptr r28 (r27), cfg/8C4 ptr r3 (r28)
cause: mwcc_dbg: stB=r33 (front-end named, two defs) is coloured AFTER codegen temps r60 (cfg ptr) and r64 (8C4 ptr) which take r3; the 10 copy temps fill r0,r4-r12, so stB falls to r27. Target needs stB coloured before r60/r64 (r60,r64->r28, r50->r27). Named single-def locals (cfg, sg declared at top) are copy-propagated to codegen temps so they do not lower the number
fix: none. Dead: bool stB = GolIsStateB(); inline GolIsStateBOf(GolSing*); stB declared before cfg; cfg inlined into GolFrame ctor arg; top-declared sg/cfg assigned later; switch(state){case 5:case 8:} (99.2, adds b L5). Needs stB to be a codegen temp with li0/conditional li1 shape
