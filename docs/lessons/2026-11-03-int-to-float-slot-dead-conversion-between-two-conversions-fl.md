# int-to-float slot: dead conversion between two conversions flips MWCC slot alternation (fn_801EC034 exact)

- status: works
- tags: int-to-float,stack-slots,RPSports_801eb388
- scope: Pack/RPSports/RPSportsCommon/RPSports_801eb388/fn_801EC034
- source: claude/801eb-1103

symptom: retail case 5 uses 0x48 for both conversions, case 6 0x50 for both; ours k-th conversion of a case got slot k
cause: MWCC picks int-to-float temp slots by conversions created (dead ones count, constant ones folded earlier do not); two conversions in one straight-line block never share a slot without an extra conversion between them
fix: (void)(f32)t; between the two conversions in each case helper (R17, ledger row 113): 8 -> 0 lines. Scratch harness: compile a tiny .cpp with the unit flags and grep lfd N(r1) to test slot rules in seconds; int-param ctor with constant 0 arg does NOT count
