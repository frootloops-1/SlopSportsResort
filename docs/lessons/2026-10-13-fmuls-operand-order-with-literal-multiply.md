# fmuls operand order with literal multiply

- status: works
- tags: fmuls,float,order
- scope: RPGol_802c16a4
- source: claude/rpgolscene-unsplit

symptom: constant-first operand order
cause: MWCC canonicalizes literal multiplies
fix: x / 2^n (folded to reciprocal multiply) or a separate statement w *= 30.0f gives computed-value-first
