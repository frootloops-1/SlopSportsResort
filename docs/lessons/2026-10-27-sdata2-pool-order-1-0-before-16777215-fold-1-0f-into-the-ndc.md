# sdata2 pool order 1.0 before 16777215: fold 1.0f into the ndc statement

- status: works
- tags: sdata2,pool-order,eggDrawPathDOF
- scope: egg/gfxe/eggDrawPathDOF
- source: claude/dof-1027

symptom: calcDepth pooled 16777215 before 1.0 (target 1.0 first); swapping operands (1.0f+ndc)*K did not change order
cause: MWCC pool order follows statement-level creation, not operand order inside one expression
fix: f32 ndc = 1.0f + clipZ / -viewZ; u32 depth = 16777215.0f * ndc; (same code, .sdata2 100)
