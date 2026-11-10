# (f32)self->cur++ as call arg gives increment-before-call

- status: works
- tags: mwcc,ordering
- scope: RPGol_802b66c4
- source: sonnet-worker

symptom: increment after call in ours
cause: separate statement after call
fix: pass (f32)self->cur++ as the argument
