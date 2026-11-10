# Field-before-constant load order via per-branch temp

- status: works
- tags: mwcc,float,ordering
- scope: RPGol_802bb044
- source: sonnet-worker

symptom: c*self->f loads constant first
cause: operand order doesn't matter; temp does
fix: f32 v = self->f; return c*v; inside each branch (not hoisted)
