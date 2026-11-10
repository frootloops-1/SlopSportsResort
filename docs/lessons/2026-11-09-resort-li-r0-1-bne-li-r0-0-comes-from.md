# resort: li r0,1; bne; li r0,0 comes from "T x = 1; if (!c) x = 0;"

- status: works
- tags: resort,codegen,branch,constant
- scope: resort
- source: RP batch 5 (2026-11-09)

symptom: ternary/if-else give branchless subic/subfe
cause: MWCC keeps the speculated constant shape only for assign-then-conditionally-overwrite
fix: write the default first, then overwrite in an if (RPSysSystem Unk_8022D650: u16 opt = 1; if (!clear) opt = 0;)
