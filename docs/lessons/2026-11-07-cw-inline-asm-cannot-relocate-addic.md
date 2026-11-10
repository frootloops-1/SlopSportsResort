# CW inline asm cannot relocate addic.

- status: fails
- tags: RPBox,asm,R17
- scope: Pack/RPSports/RPBoxScene/RPBox_802cf93c

symptom: addic. sym@l / lo() / @L all rejected; addi/lfs/lwz accept @l
cause: addic. sym@l / lo() / @L all rejected; addi/lfs/lwz accept @l
fix: use opword (DOL-exact, object loses one ADDR16_LO reloc) or keep C
