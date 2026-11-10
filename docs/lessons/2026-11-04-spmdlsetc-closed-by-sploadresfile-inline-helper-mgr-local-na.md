# SpMdlSetC closed by SpLoadResFile inline helper (mgr local + named res return); did not transfer to SpMdlSet/B/D

- status: works
- tags: inline-helper,colour,ctor,801f1d4c
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f1d4c
- source: claude/sp801f1-1104

symptom: mgr r21 vs r27 (mgr should share res's register)
cause: mgr colour picks the lowest already-used non-neighbour register; it must be coloured before the k-loop IV
fix: static inline u16 SpLoadResFile(EGG::Archive*, const char*) { RPGrpModelResManager* mgr = spCurrent; u16 res = mgr->CreateData(12, GetFileFromArchive(a, n, NULL), 0); return res; } (return-expression form and file local fail). No effect on SpMdlSet/SpMdlSetB/SpMdlSetD
