# resort: a shared state-machine template accounts for ~100 weak copies per sport

- status: works
- tags: resort,template,header
- scope: resort
- source: can-fld

symptom: repeated weak functions calling fn_803457F4/803456D0/803456D4/803456F8/803457B8 with 12-byte ptmf arrays in Frisbee Dog, Archery, Basketball
cause: Resort game code instantiates one state-machine template per class
fix: done 2026-11-09: include/Sports2/Unk_StateMachine.h (Unk_StateMachineBase + Unk_StateMachine<T>, base unit Sports2/Unk_803456D0); 34 owners, ~+250 exact. Swordplay copies not yet adopted
