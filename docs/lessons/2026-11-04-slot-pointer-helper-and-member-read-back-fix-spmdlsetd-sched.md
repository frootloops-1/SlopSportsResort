# Slot-pointer helper and member read-back fix SpMdlSetD scheduling

- status: works
- tags: schedule,helper,ctor,dependency
- scope: RPSportsCommon/RPSports_801f1d4c
- source: claude/sp801f1-1104b 8f1426452

symptom: li r3,0x10 hoisted above stw; capture slot read in wrong place
cause: Flag update through a local lets scheduler hoist; helper taking value reads slot too early
fix: SpNewCapture(&f4C[i]) slot pointer; f4C[i]->flags |= 0x80 read-back. 98.4->99.8; mgr/anm r24 vs r25 left
