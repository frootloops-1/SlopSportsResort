# BINARY section is Yaz0 strap.arc: own unit via dtk extract + pragma section

- status: works
- tags: data,binary,extract,dtk
- scope: Pack/RPSports/RPSportsCommon/RPSysStrapArchive
- source: session-2026-11-07

symptom: auto_06_80355280_BINARY 132 KB unmatched; 5 bogus lbl_ symbols mid-stream
cause: DOL section 11 (.BINARY) is one Yaz0 blob (strap.arc, 0x204FF + 1 pad) decoded by RPSysBootScene; no unit owned it
fix: one symbol size:0x20500 align:32; config.yml extract -> strap.szs.inc; RPSysStrapArchive.c: #pragma section ".BINARY" + DECL_SECTION extern const decl before the include. DOL 0
