# Non-const Mtx params let loads stay put: fn_801BEDCC 85 -> 100 without scheduling pragmas

- status: works
- tags: scheduling,const,alias,RPUtlMath,pool-order
- scope: Pack/RPUtility/RPUtlMath
- source: claude/utlmath-1027

symptom: fn_801BEDCC lerp loop stuck at 85%: prologue stw/mr interleave and arg movs differ; scheduling on/off pragmas only trade one diff for another
cause: const Mtx from/to params let the scheduler hoist loads above stack stores; the original (non-const) keeps loads/stores sequential. Pragmas were compensating
fix: declare from/to as plain Mtx, drop all #pragma scheduling hacks. Also: skip math_arithmetic.h via its include guard (NW4R_MATH_ARITHMETIC_H) + declare FrSqrt/FSqrt/U16ToF32 to avoid OSFastCast statics; sources written in descending address order; sdata2 pool order via dead literals at top of fn_801BEB1C (MATCH-PENDING)
