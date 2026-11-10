# resort: const and non-const inline getters of one member load it twice

- status: works
- tags: resort,const,inline,load-merge
- scope: resort
- source: RP batch 5 (2026-11-09)

symptom: requestNandFunc 95%: retail loads the NAND info pointer once, ours twice (or vice versa)
cause: MWCC doesn't merge loads across a const and a non-const inline getter
fix: match the constness of the original getters (RPSysSystem::getNandEndMessage non-const in Resort) - pending RPSysSystem.h
