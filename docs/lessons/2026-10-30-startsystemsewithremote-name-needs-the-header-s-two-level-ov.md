# startSystemSeWithRemote(name) needs the header's two-level overload

- status: works
- tags: rpsndaudiomgr,inline,register
- scope: Pack/RPSports/RPSportsCommon/RPSports_801eabf4

symptom: fn_801EAE50 98.4: name/mgr/flag/id registers rotated (r28-r31) around two inlined SE calls
cause: local RPSndAudioMgr copy had a one-level startSystemSeWithRemote(const char*,u32); retail uses name->id overload calling bool startSystemSeWithRemote(u32 id,u32 flag) with a success local; named const char* locals also perturbed colouring
fix: copy the header's two overloads (bool success = startSound(..id); if(success) setRemote(flag); return success) and pass string literals directly -> 100%
