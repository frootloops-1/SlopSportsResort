# Float zero kept in a register needs a local inside a static inline

- status: works
- tags: float,zero,register,inline
- scope: RPGol_802c68a4
- source: claude/rpgolscene-unsplit

symptom: orig lfs 0.0 once and reuses it for compare/sub/div; bare 0.0f literal folded into fneg/fdiv
cause: constant propagation of literal
fix: float zero = 0.0f inside a static inline helper with early return (if (zero == d) return r;) gives bne/b shape
