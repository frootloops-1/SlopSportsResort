# RPSports_801ef064: parse-time vs codegen-time pooling (aggregate inits first, code literals in compile order)

- status: works
- tags: string-pool,sdata2,rodata,pool-order,inline-deferred,RPSports_801ef064
- scope: Pack/RPSports/RPSportsCommon/RPSports_801ef064
- source: claude/sp801ef-1103

symptom: after defining data in source: GXColor templates and the local names[4] array sit at the pool head while code strings/floats follow compile order; float 0.0f/0.5f swapped in .sdata2 (objdiff still said .sdata2 100)
cause: aggregate initializers (local const char* x[N], GXColor c={..}) create their objects/strings at PARSE time in source order; code literals pool at codegen in compile order (reverse source) and in IR statement order inside a function
fix: order parse-time templates by source position (static inline helper defined AFTER its caller with a forward declaration moved {FF,FF,FF,a} behind {0,0,0,255}); move the statement using the first-pooled float first (center.z = 0.0f before the 0.5f lines). Byte-compare sections with objdump: objdiff section % missed the swap
