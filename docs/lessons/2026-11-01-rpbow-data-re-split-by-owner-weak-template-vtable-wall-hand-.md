# RPBow .data re-split by owner; weak template vtable wall (hand ctor with lbl_ names)

- status: works
- tags: splits,data,weak,template,vtable,RPBow,R17
- scope: Pack/RPSports/RPBowScene
- source: split task 2026-11-01

symptom: RPBow_8032F514 .data 0 (range held other units' objects); InitAudioActors 99.5 blocked by template vtable names
cause: weak vtable of a class with inline virtual dtor belongs to the TU that does new Class; the four TRPSnd* template weak objects live once in RPTns_8021ba24 .data (first instantiating TU); renaming forces reloc mismatches in 17 users, trailing 4-byte 0 in a vtable at a TU boundary is 8-alignment padding
fix: splits: 6B0-6C8 -> RPBow_8032ADD8, 6C8-6E8 gLaneXOffsets -> RPBowGlobalLaneManager, 6E8-700 RPBowNpcManager vtable -> RPBowManagerContext (size 0x18->0x14), 700-738 -> RPBow_80332D14; @stringBase0 0x50->0x4B; InitAudioActors hand ctor + BowNewNpcSnd wrapper (R17 row 61); format string two spaces. Later: project-wide template rename + convert 17 users
