# Target lbl_XXXX vs our named symbol shows as DATA-REF; fix is symbols.txt rename

- status: works
- tags: data,symbols,config,objdiff,reloc
- source: tools/near_miss.py --renames 2026-10-15

symptom: near_miss.py --renames: functions at 99.x% whose only diff is a relocation to lbl_80XXXXXX (target) vs a real name (ours); e.g. hd_cb, sIdleRate, __vt__19RPSysMenuKokeshiMgr
cause: objdiff matches relocations by symbol name; config/symbols.txt still has the auto lbl_ name so code that is already correct scores <100%
fix: Rename the symbol in config/RSPE01_01/symbols.txt (and any extern lbl_ users in src) to the name our build emits; conflicts (one lbl_ -> several names) mean a merged symbol that needs splitting
