# Duplicate identical pool constants in .sdata2 mean a TU boundary

- status: works
- tags: sdata2,pool-order,split,magic-double,RPSports
- scope: RPSports_801D0120
- source: claude/w-sd2-801d0120-1029

symptom: target .sdata2 holds two identical u32 magic doubles and two 0.5f; one TU always dedups them, and no pragma (push/pop, optimization_level, defer_codegen, section, fp_contract, peephole, scheduling) breaks the dedup
cause: they are two TUs: 801D0120..801D0334 (U32, 0.5) and 801D0334..801D1408 (arr, 0f 1f -1 S32 0.5 U32). The symbols.txt @NNNN names come from our old builds via pool_renames, so they are not original creation-order evidence
fix: split at 0x801D0334 (orchestrator). In TU B one dead static helper before 0334 (N_frameDown_00 findPane, 0.0f, getFrameMax()-1.0f, -1.0f) fixes both string and float order (R17). Both scratch .o match main.dol 0 bytes per section (scratch dolcmp.py)
