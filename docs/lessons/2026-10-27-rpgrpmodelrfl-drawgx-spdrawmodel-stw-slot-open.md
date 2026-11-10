# RPGrpModelRfl::DrawGX spDrawModel stw slot (open)

- status: open
- tags: mwcc,schedule,drawgx,RPGrpModelRfl
- scope: RPGrpModelRfl::DrawGX

symptom: retail: lwz,li,lis,stw spDrawModel,lbzx,addi,stb; ours puts stw after addi (2 diff lines, 99.7%)
cause: scheduler placement; stw first in source hoists it above lwz; any store before reverseCulling read forces lhz reload
fix: open. Tried all 6 orders of tevStageNum/spDrawModel/reverseCulling, temps, pointer to struct, comma expr, ternary, static inline table helper; permuter 18 min no gain
