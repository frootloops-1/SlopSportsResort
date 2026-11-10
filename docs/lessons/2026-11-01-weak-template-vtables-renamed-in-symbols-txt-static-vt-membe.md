# Weak template vtables renamed in symbols.txt; static __vt member names them in C++

- status: works
- tags: templates,vtable,symbols,weak,link
- scope: RPTns,RPBow,RPBsb,RPGol
- source: claude/mr-a-1101

symptom: lbl_803C3FC0/3FF8 could not be renamed to the mangled weak names because C++ cannot spell __vt__21TRPSndAudioHandles<8>; 17+ units extern the lbl_ names
cause: a static data member __vt in an explicit specialisation mangles to exactly the vtable symbol; defining it defines the symbol; works beside the compiler's own vptr store. Not usable in a TU that already implicitly instantiates the real template (RPBowNpcManager via RPSndObject); @STRING@ weak assert-string names cannot be reached (lbl_803C4080/4098 stay)
fix: commit 652f1879f; symbols.txt lbl_803C3FC0 -> __vt__36TRPSndAudioActorBaseWithHandles<4,4> (0x38 weak), lbl_803C3FF8 -> __vt__21TRPSndAudioHandles<8> (0x10 weak); RPTns_8021ba24 defines them; DOL 0. lbl_803C52B0 rename needs confirmed class name (BsbBallSndActor inferred); ledger row 75 documents the naming-only specialisations
