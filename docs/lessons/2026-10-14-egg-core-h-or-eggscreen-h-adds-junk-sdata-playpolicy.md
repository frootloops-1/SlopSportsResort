# egg/core.h or eggScreen.h adds junk .sdata (PlayPolicy_*)

- status: works
- tags: sdata,header,egg
- scope: RPTns_802499f8
- source: sonnet worker 2026-10-14

symptom: extra 8-byte .sdata PlayPolicy_Onetime/Loop
cause: header statics
fix: declare minimal local EGG::Screen / CoreControllerMgr views with the same mangled statics (RPTns_802499f8)
