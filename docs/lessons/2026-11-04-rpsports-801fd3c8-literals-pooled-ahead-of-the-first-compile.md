# RPSports_801fd3c8: literals pooled ahead of the first-compiled function mean file-end static helpers

- status: works
- tags: string-pool,sdata2,pool-order,inline-deferred,static-helper,RPSports_801fd3c8
- scope: Pack/RPSports/RPSportsCommon/RPSports_801fd3c8
- source: claude/sp801fd-1104

symptom: strings of fn_801FD914 (first two) and fn_801FD730's magic double/-5000.0f sit in the pool BEFORE fn_801FD3C8's literals, but fn_801FD3C8 is first in .text (compiled first); address-taken (vtable) and weak inline virtuals do not compile earlier (scratch tests: weak virtuals pool LAST)
cause: code compiled before the first emitted function: non-inline static helpers at the file end compile first at their slot, get auto-inlined into callers, and are dead-stripped at link
fix: move the literal-bearing statements into 'static void' helpers at the very end of the file (outside #pragma auto_inline off regions; forward-declare before the caller); order helpers so the earliest-pooled one is defined last. Closed .rodata/.sdata2 and also fixed fn_801FD730's colouring. R17 rows 170-172
