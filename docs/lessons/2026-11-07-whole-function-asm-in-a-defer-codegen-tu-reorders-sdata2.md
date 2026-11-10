# Whole-function asm in a defer_codegen TU reorders .sdata2

- status: works
- tags: RPBox,asm,R17
- scope: Pack/RPSports/RPBoxScene/RPBox_802cf93c

symptom: float literals in asm bodies are pooled at parse time and jump to the front of .sdata2 (58 fns regressed)
cause: float literals in asm bodies are pooled at parse time and jump to the front of .sdata2 (58 fns regressed)
fix: unused inline asm listing every pool literal in retail order, placed after the named .sdata2 consts, restores order
