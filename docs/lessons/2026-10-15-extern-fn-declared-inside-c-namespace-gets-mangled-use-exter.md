# Extern fn declared inside C++ namespace gets mangled; use extern C for fn_XXXX symbols

- status: works
- tags: reloc,extern-c,namespace
- scope: Pack/RPSports/RPBowScene

symptom: DrawBlur 99.95%: bl fn_801C3490__7BowlingFPv... instead of fn_801C3490
cause: forward decl inside namespace Bowling is C++ linkage so the call mangles
fix: extern "C" bool fn_801C3490(...); RELOC near-misses with mangled-vs-plain call names are this
