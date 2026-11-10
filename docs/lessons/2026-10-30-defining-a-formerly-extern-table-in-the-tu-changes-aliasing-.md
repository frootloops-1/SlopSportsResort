# Defining a formerly-extern table in the TU changes aliasing: const def hoists loads, non-const def sinks them

- status: open
- tags: aliasing,schedule,data-ref,sdata
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f1d4c
- source: claude/d1f1d4c-b-1031

symptom: colour copy (lbz x4) moved above stores when lbl_804C2044 became a const definition (4 fns 100->70); fn_801F27E8 table load (.sdata, non-const) sank below ctor stores (99.6->88)
cause: MWCC alias analysis: a const object cannot alias stores, a non-const global can
fix: colour: shared static inline helper with local aggregate {255,255,255,255} (one parse-time @N; helper defined between the neighbouring sdata2 tables) -> 4 fns back to 100. 27E8: reading the entry into a local before the stores gives 97.3 (register residue); static/const-cast/no-address-taken variants did not help
