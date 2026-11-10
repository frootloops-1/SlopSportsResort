# resort: singleton name strings (SDCardMgr, Nwc24Mgr, RPSysDbgScenePatroler) are weak shared .data after the strong vtables

- status: open
- tags: resort,data-order,weak,sdcardmgr,rpsyssystem

symptom: string sits after vtables in retail .data; every local-static/inline/specialization spelling emits it first
cause: MWCC Wii/1.0-1.7: inline/template local statics and explicit specializations are emitted at parse time; only a generic template static data member lands after strong vtables (still before weak vtables first needed by __sinit). In RPSysSystem that form gives exact .data but moves ConfigData getters before __sinit (128 bytes)
fix: Construct still unknown; accessors are placeholders in include/Pack/RPSystem/RPSysUnkSingletons.h
