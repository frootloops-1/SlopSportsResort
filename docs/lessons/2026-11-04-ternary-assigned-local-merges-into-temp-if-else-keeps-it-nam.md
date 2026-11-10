# Ternary-assigned local merges into temp; if/else keeps it named (b340 C530)

- status: works
- tags: register,ternary,merge,declaration-order,float
- scope: RPSportsCommon/RPSports_8020b340
- source: claude/b340-1104c 2e7330046

symptom: float local coloured as temp vs named variable
cause: x = c ? a : b merges x into the high temp (coloured first); if/else assignment keeps x a named local. Store with no frsp + separate frsp = f32 stored directly plus a double copy
fix: Choose ternary vs if/else per needed colour class; declare-then-assign order; cx=(f64)c for the split frsp. C530 99.1->100 (R17 row 213 for decl order + f64)
