# hand vtables after jump tables: #pragma defer_codegen off + extern first + explicit_zero_data (801f1d4c)

- status: works
- tags: defer_codegen,vtable,jump-table,sdata2,RPSports_801f1d4c
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f1d4c

symptom: hand void*[] vtables land before the jump table under -inline deferred; .data 46%
cause: initialized globals emit at parse time
fix: #pragma defer_codegen off puts them after jump table; first definition after pragma still emitted before flush so declare plain extern first; all-zero vtable needs #pragma explicit_zero_data on else .bss; weak @STRING@ objects emitted in class member declaration order, only for expanded inlines; keep symbols.txt entries for them scope:local (weak names merge with egg Frustum unit, DOL .data -152 at flip); never-called helper calling the inline pools its literals at its slot; const char* const + DECL_SECTION .sdata restores hoisted table loads; objdiff pairs any @N sdata2 name
