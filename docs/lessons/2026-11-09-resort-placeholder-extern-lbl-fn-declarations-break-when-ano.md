# resort: placeholder extern lbl_/fn_ declarations break when another branch names the symbol

- status: works
- tags: resort,merge,symbols,placeholders
- source: 2026-11-09 merge

symptom: link: undefined lbl_806F4C68 from RPGrpCamera after merging rp-savedatamgr
cause: camera declared extern void* lbl_806F4C68; the other branch proved it is RPSysSystem::spInstance
fix: use real declarations (RPSysSystem::instance()->Unk_80237918()); avoid extern placeholders for symbols a header can declare
