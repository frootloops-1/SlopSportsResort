# Jump table for an asm function

- status: works
- tags: RPBox,asm,R17
- scope: Pack/RPSports/RPBoxScene/RPBox_802cf93c

symptom: hand table lands in wrong .data slot
cause: hand table lands in wrong .data slot
fix: static void* table of fn+offset; compile earlier functions first in #pragma defer_codegen off region; rename the anonymous @NNNN in symbols.txt so objdiff pairs it
