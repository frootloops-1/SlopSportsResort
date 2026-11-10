# 8-byte pool object read as sym+4

- status: works
- tags: RPBox,R17
- scope: Pack/RPSports/RPBoxScene/RPBox_802de63c

symptom: 8-byte pool object read as sym+4
cause: 8-byte pool object read as sym+4
fix: C member/array read gives li + lfs 4(r3); symbolic asm lfs v, sym+4 reproduces the sda21+4 reloc
