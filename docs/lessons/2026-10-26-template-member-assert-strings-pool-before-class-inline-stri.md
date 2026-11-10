# Template-member assert strings pool before class-inline strings; forward via a later class inline

- status: works
- tags: weak-string,template,emission-order,RPSndAudioMgr
- scope: Pack/RPAudio/RPSndAudioMgr

symptom: objdiff 100% but DOL differs: weak @STRING@ pool order (EGG TAudioSound3DMgr<4>::setCameraCount strings first, retail has getFanfareLength strings first)
cause: Template member instantiated at the use site in a cpp function creates its @STRING@ before the class-inline (in-class) function strings; source position of the caller does not matter (moving configureMiniGame to file end no change); local out-of-line template member copy fails to inline
fix: Add a class inline wrapper in the header defined after the relevant class inline (setCameraCountRP after getFanfareLength) and call it: template instantiation then happens at class-inline processing and strings land after. Needs MATCH-PENDING (R17) + ledger row. DOL 282 -> 0 bytes.
