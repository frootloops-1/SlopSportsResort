# F1 sym diff lbl_ vs named static member: use the lbl_ extern in source for that address

- status: works
- tags: F1,sym
- scope: RPSports_801ef064
- source: claude/nm-data

symptom: target lbl_804BF740 vs ours spInstance__14RPSysPlayerMgr, name already exists elsewhere so rename impossible
cause: name collision between two statics
fix: in the unit use the extern lbl_ already declared instead of the class accessor; RPSports_801ef064 fn_801EFA00 100
