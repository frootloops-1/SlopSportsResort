# Header-induced sdata2 shift: replace heavy headers by local class views; pool order via dead literal (801E51B4)

- status: works
- tags: sdata2,headers,local-view,pool-order,flip-gate
- scope: RPSports_801E51B4
- source: orchestrator 2026-11-03

symptom: unit .sdata/.sdata2 larger than retail (8 bytes lead), DOL diffs 1153 bytes (rodata local array first, sdata2 offsets)
cause: eggScreen.h/RPSysCursorDrawMgr.h/RPSysResourceManager.h include nw4r/g3d, emitting weak @LOCAL@GetAnmPlayPolicy policyTable into sdata2; function-local const array pooled at offset 0 of .rodata before file-scope tables; literal pool follows first use
fix: local views of the 3 classes (no header); define rodata tables above the function holding the local const array; (void)-5000.0f dead literal (R17 ledger 119); use flip_gate --keep + byte-level DOL compare to localise DOL diffs; do not git checkout a dirty source file mid-experiment
