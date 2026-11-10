# x * 0.5f operand order: write x / 2.0f

- status: works
- tags: mwcc,fp,literal,pool
- source: RPUtl_801C9E7C

symptom: lfs 0.5 loaded before the member, fmuls operand order flipped
cause: MWCC canonicalises literal multiply operand first; division by 2.0f becomes a multiply with the literal second
fix: scale.x / 2.0f (pool entry is still 0.5f)
