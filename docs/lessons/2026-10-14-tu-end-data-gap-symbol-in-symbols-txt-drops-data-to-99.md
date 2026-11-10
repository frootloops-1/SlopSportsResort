# TU-end .data gap_ symbol in symbols.txt drops .data to 99%

- status: works
- tags: symbols,data
- scope: RPGol_802b7670
- source: RPGol_802b7670

symptom: .data 99.03
cause: explicit gap_ symbol
fix: delete the gap_XX_..._data line
