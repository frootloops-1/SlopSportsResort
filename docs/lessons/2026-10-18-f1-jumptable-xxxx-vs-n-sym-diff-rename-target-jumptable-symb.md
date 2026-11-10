# F1 jumptable_XXXX vs @N sym diff: rename target jumptable_ symbol to our @N

- status: works
- tags: F1,jumptable
- scope: RPSports_801f9150,RPBsb_8027a3c4
- source: claude/nm-data

symptom: 99.4% sym diff jumptable_803C2F20 vs @2732
cause: name only
fix: rename target symbol to @N scope:local even if offsets differ (RPSports_801f9150, RPBsb_8027a3c4); ...data.0 section-anchor base cannot be fixed by naming (fn_8027B020 99.9)
