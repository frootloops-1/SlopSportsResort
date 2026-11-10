# Seed only .float/.double pool objects

- status: works
- tags: seed,sdata2,GXColor
- scope: RPBoxScene
- source: RPBox_802f438c

symptom: extra 4-byte pool entry 0x80808000
cause: anonymous GXColor aggregate in .sdata2 seeded as an f32 literal with the same bits
fix: asm2cw --seed skips objects whose first directive is not .float/.double
