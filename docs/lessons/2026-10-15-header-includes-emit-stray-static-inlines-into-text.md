# Header includes emit stray static inlines into .text

- status: works
- tags: headers,text
- scope: RPTnsScene
- source: claude/rptns-3

symptom: unused MEM/GX/OS bodies appear in unit
cause: RPSndAudioMgr.h etc. include inline helpers
fix: drop include; use local class views with same mangled names
