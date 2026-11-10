# resort: RPSysHomeMenuMgr TU starts at 0x80242750 (BanIcon + Unk_806F4D50 singleton)

- status: works
- tags: resort,rp

symptom: unit pool/sbss shared with unk/text_80242750
cause: one TU split in two
fix: merge the unk split into RPSysHomeMenuMgr; 0/15 -> 19/23
