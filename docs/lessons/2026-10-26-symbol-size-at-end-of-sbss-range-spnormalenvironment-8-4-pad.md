# Symbol size at end of sbss range: spNormalEnvironment 8 -> 4 (pad belongs outside symbol)

- status: works
- tags: sbss,symbols.txt,size,eggLightTexture
- scope: egg/gfxe/eggLightTexture
- source: lt-data-1026

symptom: sbss 88.9%, SIZE-MISMATCH 8!=4
cause: symbols.txt size included trailing alignment pad
fix: size:0x4 then re-run dtk split
