# Pre-RA scheduler: mr rank 0 beats li rank 4 at equal height

- status: works
- tags: schedule,mr,li,iv,dependence
- scope: global
- source: claude/b340-1104f

symptom: retail li,li,mr,mr but ours mr,mr,li,li with identical pre-schedule order
cause: GC/3.0a5.2 pre-RA scheduler prefers mr over li at equal height; retail order implies a different dependence graph, not declaration order
fix: Look for source changing the dependence graph (what the IVs depend on), not decl order (b340 E58C open)
