# RPSysSceneCreator flip blocked by implicit weak dtor emission order

- status: open
- tags: link-flip,weak-order,implicit-dtor,RPSysSceneCreator,C5
- scope: Pack/RPSystem/RPSysSceneCreator
- source: claude/nm-link-1 2026-10-15

symptom: All 15 fns exact; flip + DOL link: 20651 bytes differ, 189 symbols moved; first: __dt__10RPSysSceneFv orig 0x80183FA8 linked +1212.
cause: Orig .text order: ~RPSysSceneCreator, ~RPSysScene (implicit), createSportsScene, ~RPSportsBaseScene (implicit), getAudioType... Ours: ~RPSysSceneCreator, createSportsScene, ~RPUtlLoadSaveDataScene (absent from orig), ~RPSportsBaseScene, ~RPSysScene. Implicit dtors are emitted at first need; the orig needs ~RPSysScene before createSportsScene (reverse source order), and never instantiates ~RPUtlLoadSaveDataScene here. Not a symbols.txt issue (plan hypothesis wrong).
fix: None yet (Opus C5 candidate). Ideas: which function first instantiates ~RPSysScene in orig (createPartyScene? a delete in destroy?); whether RPUtlLoadSaveDataScene has an out-of-line dtor in its own TU.

O1 (Opus, 2026-10-15, claude/nm-weak-1): order half SOLVED, flip still blocked.
- `DECOMP_FORCEACTIVE_DTOR(RPSysSceneCreator, RPSysScene);` placed after createSportsScene's `#endif` (before the PACK_PARTY block) puts every symbol of the TU's .text range 0x80183F68-0x80184E80 at its original address (helper is dead-stripped at link). Likely orig cause: a dead-stripped function between them in source (createPartyScene-like) needed ~RPSysScene first. Explicit inline `virtual ~RPSysScene() {}` / `~RPSportsBaseScene() {}` changes nothing.
- Remaining blocker: our .o emits 13 weak scene vtables (RPTns, RPGol, RPGolCourseSelect, RPBsb, RPBox, RPBow, RPSports menu/physical/title/main scenes, RPUtlLoadSaveDataScene, RPSysNunchukCheckScene) which pull RPSysScene weak stubs (ListenPropertyEvent..taskAsync, @36@/@68@ ~RPSysNunchukCheckScene thunks) into the TU: +0x44 bytes after CreateInstance. Orig has those vtables in their own units (e.g. __vt__10RPTnsScene 0x803C3730), so those classes need an out-of-line key virtual (declared non-inline dtor) in their headers. Then re-apply the macro and relink.
- Flipped-alone dol_diff is ~326k bytes (relocs from earlier units into the shifted range); 0 is the only criterion.
