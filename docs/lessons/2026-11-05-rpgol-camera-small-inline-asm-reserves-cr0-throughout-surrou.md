# RPGol camera small inline asm reserves CR0 throughout surrounding C++

- status: fails
- tags: RPGol_802c441c,asm,regalloc,CR0
- scope: golShotKindB fn_802C531C
- source: docs/tasks/RPGol_802c441c.md

symptom: Short inline asm materializes bool and halfword chain in correct GPRs but whole function has 26 differing instructions
cause: Visible CR0 compare/andi clobbers make compiler allocate surrounding comparisons to CR1. Hiding compares/branches with opword loses implicit GPR/CR liveness and causes deletions or branch simplifications
fix: Reject short block. Five additional parameter types and six declaration orders did not close; eight opaque-opcode combinations failed. Full scheduled native fallback with explicit retail frame avoids global CR allocation effects.
