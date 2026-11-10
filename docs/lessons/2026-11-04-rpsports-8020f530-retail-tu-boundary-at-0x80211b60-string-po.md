# RPSports_8020f530: retail TU boundary at 0x80211B60 (string pool first in .rodata is the tell)

- status: works
- tags: splits,tu-boundary,rodata,rpsports,8020f530
- source: sp8020f-1104

symptom: .rodata had @stringBase0 BEFORE the local @N arrays (unique in the game); sdata wide strings, 500.0f, MailHolder vtable all used only by 11B60+
cause: two TUs: physical-test layout (F530-11B60) and TrainingMenu/mail holder (11B60-14480)
fix: split splits.txt at .text 0x80211B60/.rodata 0x8038B170/.data 0x803C3718/.sdata 0x804BDDC8/.sdata2 0x804C2330 (sbss to the new unit); new NonMatching RPSports_80211b60.cpp; all data sections 100 in both
