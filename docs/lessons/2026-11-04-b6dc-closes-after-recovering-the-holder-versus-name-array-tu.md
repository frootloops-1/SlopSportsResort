# B6DC closes after recovering the holder versus name-array TU boundary

- status: works
- tags: fn_8020B6DC,RPSports_8020b340,split,anchor,vtable
- scope: Pack/RPSports/RPSportsCommon/RPSports_8020b340
- source: codex-b6dc-1104

symptom: B6DC 99.3: every name-array offset was +0x10 because a preceding manual holder vtable joined the section anchor.
cause: The combined unit included two holder functions and their 16-byte vtable before the table-owning translation unit.
fix: Split at text 0x8020B340 and data 0x803C3528; keep holder text 0x8020B294-0x8020B340 and data 0x803C3518-0x803C3528 in original unit. Add local ...data.0 label and four array symbols. B6DC body unchanged, 100%; all 448 bytes after 16 relocations match the original DOL. Four data sections 100, no regressions; combined scope 30/41.
