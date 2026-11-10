# Converting extern lbl_X+off string hacks to literals fails: pool order is first-use order

- status: fails
- tags: F1,strings
- scope: RPSysLytPlayerSelect
- source: claude/nm-data

symptom: pool grows 0x5c7 to 0x606 and offsets shift
cause: MWCC orders the string pool by first use; original function order differs
fix: keep the extern lbl_+offset hack and make stray literals use it
