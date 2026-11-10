# Coalesce if/else branch locals by declaring once at function top

- status: works
- tags: mwcc,regalloc
- scope: RPTns_8023c74c
- source: claude/rptns-2

symptom: anm pointer r26 in else branch vs r27 in orig (if-branch matched)
cause: separate block-scoped decls get separate priority
fix: TnsAnm* anm; declared at top, assigned in both branches
