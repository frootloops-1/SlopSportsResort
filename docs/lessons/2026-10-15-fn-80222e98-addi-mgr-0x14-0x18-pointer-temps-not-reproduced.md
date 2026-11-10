# fn_80222E98 addi mgr+0x14/+0x18 pointer temps not reproduced

- status: fails
- tags: addressing,addi,pointer
- scope: RPTns
- source: RPTns_80222a70

symptom: orig addi r31,mgr,0x14 and addi r5,mgr,0x18; ours folds to offsets
cause: unknown
fix: pointer vars, references, inline pointer helpers all <=94.4
