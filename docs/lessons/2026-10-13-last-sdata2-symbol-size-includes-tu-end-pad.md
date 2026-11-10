# Last .sdata2 symbol size includes TU-end pad

- status: works
- tags: sdata2,symbols
- scope: RPGol_802b6a58
- source: opus-worker

symptom: .sdata2 94.7 with identical bytes
cause: size 0x8 covers pad
fix: set size to 0x4
