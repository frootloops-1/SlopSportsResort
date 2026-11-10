# .sdata2 TU-end padding to 8 reveals a TU split

- status: works
- tags: split,sdata2,evidence
- scope: RPGol_802bca94
- source: opus-worker

symptom: unreferenced zero word after a 4-byte literal; .sdata2 80%
cause: each TU pool padded to 8
fix: split there (RPGol_802bca94 at 0x802BDD70)
