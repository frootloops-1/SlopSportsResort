# RPSysSceneCreator flip: out-of-line dtor decl on scene classes makes their vtables external

- status: works
- tags: link-flip,weak-vtable,key-function,RPSysSceneCreator,symbols
- scope: Pack/RPSystem/RPSysSceneCreator
- source: claude/scenecreator-1027 2026-10-27

symptom: All fns exact but flip blocked: TU emitted 13 weak scene vtables + RPSysScene weak stubs that the orig keeps in the scenes' own units; .data 31%, .rodata 47%.
cause: Stub scene classes declared no non-inline virtual, so MWCC emitted each vtable weak wherever 'new Scene()' inlined the ctor.
fix: Declare 'virtual ~X();' (never defined) in the 14 scene headers so vtables are U refs; DECOMP_FORCEACTIVE_DTOR(RPSysSceneCreator, RPSysScene) after createSportsScene fixes ~RPSysScene order; merge 25 lbl_ strings into one @stringBase0 (size 0x15E) in symbols.txt, vt size 0x18->0x14. Flip Matching: DOL 0 bytes. Weak EGG::SceneCreator vtable left in .o (dead-stripped; objdiff .data 87%).
