# RPSports_80206a10 closed: generated sinit inherits tail unroll pragma; array registers every element

- status: works
- tags: RPSports_80206a10,sinit,unroll,pragma,bss,ctors
- scope: Pack/RPSports/RPSportsCommon/RPSports_80206a10
- source: codex-rpsports-80206a10-1104

symptom: 14/17 exact; manually initialized 15 records at 85%; natural C++ initializer spilled and stayed ~79% despite correct BSS layout
cause: Former unsplit TU ended with opt_unroll_loops off, affecting deferred generated initializer; MWCC registers each array element separately, not only the entire array
fix: Use SpEnt[15] with record temporary arguments and copy-then-metadata loop; reset opt_unroll_loops at TU tail. Split 15 local 12-byte BSS registrations; inline entry destructor for post-sinit emission. Small closes: two-word s32 array copy and const self param. All sections 100 and DOL 0; R17 facade/vtable ledger 201/202.
