# Dense 0..20 state machine: if/else-if chain on local copy, not switch

- status: works
- tags: switch,statemachine

symptom: switch would emit a jump table; orig is a cmpwi chain
cause: MWCC emits jump table for dense switch
fix: if/else-if chain over a local s32 state (fn_801E23B0)
