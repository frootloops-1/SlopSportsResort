# u8-returning call compared then incremented: use unsigned local

- status: works
- tags: u8,clrlwi,cmplwi
- scope: RPGol_802c16a4
- source: claude/rpgolscene-unsplit

symptom: orig clrlwi r3,r3,24 + cmplwi
cause: local type
fix: unsigned c = f(); (u8 c -> clrlwi r0; int c -> cmpwi)
