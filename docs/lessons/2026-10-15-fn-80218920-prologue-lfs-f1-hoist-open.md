# fn_80218920 prologue lfs f1 hoist (open)

- status: fails
- tags: schedule,prologue
- source: RPTns_80216810

symptom: Target hoists lfs f1,0(r4) above const load and fcmpo above stw r31/mr r31,r4
cause: unknown
fix: 15 forms failed: local copy, swapped operands, else-if, ternary, bool/u8 return, late ptr copy, TnsVec3* param
