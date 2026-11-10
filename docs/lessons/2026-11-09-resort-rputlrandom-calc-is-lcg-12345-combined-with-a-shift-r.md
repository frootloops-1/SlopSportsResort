# resort: RPUtlRandom::calc is LCG+12345 combined with a shift-register word

- status: works
- tags: resort,RPUtlRandom
- scope: resort
- source: RP batch 4 (2026-11-09)

symptom: SelectBallForNPC callee getU32 at 0x8025C9B0 does not match the ogws calc
cause: Resort generator: seed*0x41C64E6D+12345 xor LFSR state (if s&1 s^=0x11020; s>>=1) at 0x806F4E3C
fix: RPUtlRandom.h Resort calc; getU32 is an out-of-line weak copy
