# opaque asm-initialised pointer stops MWCC hoisting loads above stores

- status: works
- tags: RPBox,R17
- scope: Pack/RPSports/RPBoxScene/RPBox_802de63c

symptom: opaque asm-initialised pointer stops MWCC hoisting loads above stores
cause: opaque asm-initialised pointer stops MWCC hoisting loads above stores
fix: fn_802DEB34 91.9 -> 98.6 with asm-initialised force pointer
