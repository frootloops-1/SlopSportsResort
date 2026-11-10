# fn_8024C914 closed: inline getter makes named local coloured before a global-load temp

- status: works
- tags: RPTnsScene,regalloc,inline-getter,gpr
- scope: Pack/RPSports/RPTnsScene/RPTns_8024c194

symptom: fn_8024C914 99.7: archive (lwz 0x20(r5)) and spCurrent models swapped r20/r21
cause: mwcc_dbg: named archive = vreg 58, models copy-propagated to load temp @861 = vreg 65; ascending sweep pushes 58 first so 65 is coloured first (lowest reg)
fix: archive = TnsGetArchive() (static inline returning *(void**)(spInstance+0x20)): return temp numbered > 65 -> archive r20 -> 100 (MATCH-PENDING R17, ledger 135). Decl-order swaps of head/models/archive: no change.
