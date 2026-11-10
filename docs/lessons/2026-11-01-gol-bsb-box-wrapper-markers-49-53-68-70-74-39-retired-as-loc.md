# Gol/Bsb/Box wrapper markers 49/53/68/70/74/39 retired as local-view members; 62 reduced

- status: works
- tags: markers,retire,accessor,vtable
- scope: RPGol,RPBsb,RPBox,RPSports
- source: claude/mr-d-1101

symptom: invented free static inlines in 7 units
cause: no real owner exists in include/: moving each to a member inline of the unit's local view class keeps bytes (BsbResultData::getScore also drops pSi=&si steering); fn_802C0C50 and fn_802BE034 share vtable slot 5 so const void* is the shared param type (void* in 802BE034 = 98.7); GolStrBuf::getName still needs its named result local (99.5 without); row 36: setDrawGroup(u8) setter and single store both 99.9
fix: commit 78f9f1e3c; rows 36/40 stay
