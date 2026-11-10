# Physical register names in mixed asm reserve them function-wide

- status: fails
- tags: RPBox,asm,R17
- scope: Pack/RPSports/RPBoxScene/RPBox_802cf93c

symptom: fcmpo cr0 in a symbolic asm block pushed all C compares to cr1
cause: fcmpo cr0 in a symbolic asm block pushed all C compares to cr1
fix: only symbolic names in asm mixed with C
