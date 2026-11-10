# F1 sym: extern declared inside namespace gets mangled x__7Bowling; declare globals outside the namespace

- status: works
- tags: F1,namespace,sym
- scope: RPBowBackgroundNpcManager
- source: claude/nm-data

symptom: target lbl_804BF9F8 vs ours lbl_804BF9F8__7Bowling
cause: extern u8 inside namespace Bowling
fix: move extern above namespace (RPBowBackgroundNpcManager Render to 100)
