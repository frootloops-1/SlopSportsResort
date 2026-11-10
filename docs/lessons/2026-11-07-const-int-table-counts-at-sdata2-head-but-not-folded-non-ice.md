# const int table counts at .sdata2 head but not folded: non-ICE initializer

- status: works
- tags: sdata2,const,folding,data-order,RPBow_80320EFC
- scope: Pack/RPSports/RPBowScene/RPBow_80320EFC

symptom: flip gate fails (sdata2 shifted 8 bytes) because two const ints defined at file end are emitted after the literal pool; defining them at the top lets MWCC fold them (codegen regresses)
cause: MWCC emits named .sdata2 objects at their definition (defer_codegen off) and folds const ints whose initializer is an integral constant expression
fix: extern const int x = 16.0f; before the functions (R17 ledger 275): emitted first, value 16, never folded. Dead: = 16 (folds), array[1]/[2], const volatile (hoisting changes), defer_codegen on (reorders .text).
