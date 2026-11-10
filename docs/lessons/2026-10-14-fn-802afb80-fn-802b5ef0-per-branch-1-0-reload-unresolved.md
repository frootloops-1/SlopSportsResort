# fn_802AFB80/fn_802B5EF0: per-branch 1.0 reload unresolved

- status: fails
- tags: float,literal-reuse
- scope: RPGolScene
- source: claude/rpgol-family

symptom: 93.4%: target reloads 1.0 in each else sub-block, reads lbl_804BE880 first; ours reuses one 1.0
cause: unknown; MWCC reuses same-value literals across blocks
fix: Not found: flat code, helpers (remap/min), ?:, double/int 1, dummy params; remap helper fixes lbl_804BE880 position but 92.7
