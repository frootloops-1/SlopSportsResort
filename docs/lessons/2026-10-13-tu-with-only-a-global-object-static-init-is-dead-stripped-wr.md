# TU with only a global-object static init is dead-stripped: wrap array in #pragma force_active

- status: works
- tags: ctors,sinit,dead-strip,RP_80186E40
- scope: RP_80186E40
- source: sonnet

symptom: 2/2 fns exact (after naming __sinit_\X_cpp and __arraydtor$70 in symbols.txt) but DOL 0x74 text shorter; object absent from ELF
cause: mwld strips the TU: nothing references the generated __sinit
fix: #pragma force_active on / reset around the global array definition; rename fn_ symbols to __sinit_\<unit>_cpp and __arraydtor$N (scope:local) so objdiff pairs
