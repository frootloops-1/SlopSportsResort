# defer_codegen off folds visible extern const initialisers into literals

- status: fails
- tags: sdata2,pragma,pool
- scope: RPUtlDohGraphSun
- source: claude/rputl-doh-1027

symptom: after #pragma defer_codegen off, refs to lbl_ consts become @N and 1.0f*x folds
cause: const objects with visible initialisers before use are constant-propagated
fix: do not use defer_codegen off to reorder named float pools; use literals
