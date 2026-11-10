# RPGrpModelRfl DrawGX full const method and setup helpers do not free the store schedule

- status: fails
- tags: RPGrpModelRfl,DrawGX,mwcc,scheduling,const,alias
- scope: RPGrpModelRfl::DrawGX

symptom: stw spDrawModel remains after lbzx and addi, instead of before both; 38 of 39 functions exact.
cause: Earlier const-this harness result does not transfer to the full function: const DrawGX plus const spDrawModel still emits the same ordering (compared after normalizing method name).
fix: No gain from volatile store/load, restricted type pointer, const-reference getter, pointer-to-member, moving global definition, scalar/const-pointer/const-member/static-const setup helpers, pointer casts/union, or identical-arm and duplicate-store markers. schedule once regresses to 91.6 percent; whole-function inline helper is not inlined. Reverted all experiments; only BSS declaration-order fix retained.
