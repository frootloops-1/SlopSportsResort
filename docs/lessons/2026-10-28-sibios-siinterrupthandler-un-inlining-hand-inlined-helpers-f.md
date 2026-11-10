# SIBios SIInterruptHandler: un-inlining hand-inlined helpers fixed a whole-function register shift

- status: works
- tags: SIBios,SIInterruptHandler,register,inline,helper-recovery
- source: other SI decomp full match (SDK build differs, still transferred)

symptom: 98.8%, sr in r18 vs target r26, every later local shifted by one; permuter and 20+ spellings no gain
cause: We hand-inlined SITransferNext and SIGetResponseRaw (plus an invented SIGetResponseRawSr) and declared locals per block; the original had real static helpers auto-inlined and locals declared at function top, which changes MWCC local numbering/liveness
fix: Write the helpers as separate static functions, call them, declare locals at top. Rule: when a function mixes domain steps with open-coded loops of another operation, restore the helper as a static function instead of expanding it
