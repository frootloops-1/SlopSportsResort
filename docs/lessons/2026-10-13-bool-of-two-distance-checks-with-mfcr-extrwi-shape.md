# bool && of two distance checks with mfcr/extrwi. shape

- status: works
- tags: bool,mfcr,cror,inline
- scope: RPGol_802c58d4
- source: claude/rpgolscene-unsplit

symptom: orig uses mfcr; extrwi. for a bool combining two comparisons; return A && B gives ble/li/b
cause: expression shape
fix: bool r = F(a); if (r) r = G(b); return r; with inline helpers returning lenSq() > lim; pass vec pointers (z-first load order)
